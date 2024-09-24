#include "../../includes/sockets/web.hpp"

WebServer::WebServer() {}

WebServer::~WebServer() {
    for (std::map<int, ServerBlock>::iterator it = servers_map.begin(); it != servers_map.end(); ++it) {
        close(it->first);
    }
}

void WebServer::setupServers(std::vector<ServerBlock> prep_servers) {
    servers = prep_servers;
    bool is_set;
    for (std::vector<ServerBlock>::iterator it = servers.begin(); it != servers.end(); ++it) {
        is_set = false;
        for (std::vector<ServerBlock>::iterator it2 = servers.begin(); it2 != it; ++it2) {
            if (it->getPort() == it2->getPort() && it->getHost() == it2->getHost()) {
                is_set = true;
                it->setFd(it2->getFd());
                break;
            }
        }
        if (!is_set) {
            it->setupServer();
        }
    }
}

void WebServer::addToSet(const int fd, fd_set &set) {
    FD_SET(fd, &set);
    if (fd > biggest_fd)
        biggest_fd = fd;
}

void WebServer::removeFromSet(const int fd, fd_set &set) {
    FD_CLR(fd, &set);
    if (fd == biggest_fd)
        --biggest_fd;
}

void WebServer::initSets() {
    FD_ZERO(&recv_fd);
    FD_ZERO(&write_fd);
    for (std::vector<ServerBlock>::iterator it = servers.begin(); it != servers.end(); ++it) {
        if (listen(it->getFd(), 512) < 0) {
            printf("Listen error\n");
            exit(1);
        }
        if (fcntl(it->getFd(), F_SETFL, O_NONBLOCK) < 0) {
            printf("Fcntl error\n");
            exit(1);
        }
        addToSet(it->getFd(), recv_fd);
        servers_map.insert(std::make_pair(it->getFd(), *it));
    }
    biggest_fd = servers.back().getFd();
}

void WebServer::closeConnection(const int fd) {  // not sure if this condition is correct
    if (FD_ISSET(fd, &write_fd)) {
        FD_CLR(fd, &write_fd);
        if (fd == biggest_fd)
            --biggest_fd;
    }
    if (FD_ISSET(fd, &recv_fd)) {
        FD_CLR(fd, &recv_fd);
        if (fd == biggest_fd)
            --biggest_fd;
    }
    close(fd);
    clients_map.erase(fd);
}

void WebServer::acceptNewConnection(ServerBlock &server) {
    struct sockaddr_in addr;
    unsigned long addr_len = sizeof(addr);
    Client client(server);
    int new_fd = accept(server.getFd(), (struct sockaddr *)&addr, reinterpret_cast<socklen_t *>(&addr_len));
    if (new_fd == -1) {
        printf("Accept error\n");
        return;
    }
    FD_SET(new_fd, &recv_fd);
    if (new_fd > biggest_fd)
        biggest_fd = new_fd;
    if (fcntl(new_fd, F_SETFL, O_NONBLOCK) == -1) {
        printf("Fcntl error\n");
        FD_CLR(new_fd, &recv_fd);
        if (new_fd == biggest_fd)
            --biggest_fd;
        close(new_fd);
        return;
    }
    client.client_fd = new_fd;
    if (clients_map.count(new_fd) != 0)
        clients_map.erase(new_fd);
    clients_map.insert(std::pair<int, Client>(new_fd, client));
}

void WebServer::assignServer(Client &client) {
    for (std::vector<ServerBlock>::iterator it = servers.begin(); it != servers.end(); ++it) {
        if (client.server.getHost() == it->getHost() &&
            client.server.getPort() == it->getPort() &&
            client.server.getServerName() == it->getServerName()) {
            client.server = *it;
            return;
        }
    }
}

void WebServer::handleReqBody(Client &client) {
    if (client.request.body.empty()) {
        std::string tmp;
        std::fstream file;(client.response.cgi_resp.path.c_str());
        std::stringstream ss;
        ss << file.rdbuf();
        tmp = ss.str();
        client.request.body = tmp;
    }
}

void WebServer::readRequest(const int &fd, Client &client) {
    char buf[MESSAGE_BUFFER];
    int bytes_read;
    bytes_read = recv(fd, buf, sizeof(buf), 0);
    if (bytes_read == -1) {
        closeConnection(fd);
        return;
    }
    else if (bytes_read == 0) {
        closeConnection(fd);
        return;
    }
    else {
        client.request.reqParse(buf, bytes_read);
        memset(buf, 0, sizeof(buf));
    }
    assignServer(client);
    client.response.request = client.request;
    client.response.createResponse();
    if (client.response.cgi) {
        handleReqBody(client);
        FD_SET(client.response.cgi_resp.pipe_in[1], &write_fd);
        if (client.response.cgi_resp.pipe_in[1] > biggest_fd)
            biggest_fd = client.response.cgi_resp.pipe_in[1];
        FD_SET(client.response.cgi_resp.pipe_out[0], &recv_fd);
        if (client.response.cgi_resp.pipe_out[0] > biggest_fd)
            biggest_fd = client.response.cgi_resp.pipe_out[0];
    }
    FD_CLR(fd, &recv_fd);
    if (fd == biggest_fd)
        --biggest_fd;
    FD_SET(fd, &write_fd);
    if (fd > biggest_fd)
        biggest_fd = fd;
}

void WebServer::sendCGIBody(Client &client, CGI &cgi) {
    int bytes_sent;
    std::string &msg = client.request.body;
    if (msg.length() == 0)
        bytes_sent = 0;
    else if (msg.length() >= MESSAGE_BUFFER)
        bytes_sent = send(cgi.pipe_in[1], msg.c_str(), MESSAGE_BUFFER, 0);
    else
        bytes_sent = send(cgi.pipe_in[1], msg.c_str(), msg.length(), 0);
    if (bytes_sent < 0) {
        FD_CLR(cgi.pipe_in[1], &write_fd);
        if (cgi.pipe_in[1] == biggest_fd)
            --biggest_fd;
        close(cgi.pipe_in[1]);
        close(cgi.pipe_out[1]);
        client.response.code = 500; // (maybe need to make few more changes here)
    }
    else if (bytes_sent == 0 || (size_t) bytes_sent == msg.length()) {
        FD_CLR(cgi.pipe_in[1], &write_fd);
        if (cgi.pipe_in[1] == biggest_fd)
            --biggest_fd;
        close(cgi.pipe_in[1]);
        close(cgi.pipe_out[1]);
    }
    else
        msg = msg.substr(bytes_sent);
}

void WebServer::readCGIResponse(Client &client, CGI &cgi) {
    char buf[MESSAGE_BUFFER * 2];
    int bytes_read;
    bytes_read = read(cgi.pipe_out[0], buf, sizeof(buf));
    if (bytes_read == -1) {
        FD_CLR(cgi.pipe_out[0], &recv_fd);
        if (cgi.pipe_out[0] == biggest_fd)
            --biggest_fd;
        close(cgi.pipe_in[0]);
        close(cgi.pipe_out[0]);
        client.response.cgi = 2;
        client.response.code = 500;
    }
    else if (bytes_read == 0) {
        FD_CLR(cgi.pipe_out[0], &recv_fd);
        if (cgi.pipe_out[0] == biggest_fd)
            --biggest_fd;
        close(cgi.pipe_in[0]);
        close(cgi.pipe_out[0]);
        int status;
        waitpid(cgi.pid, &status, 0);
        if (WEXITSTATUS(status) != 0)
            client.response.code = 502; // (maybe need to make few more changes here)
        client.response.cgi = 2;
        if (client.response.response.find("HTTP/1.1") == std::string::npos)
            client.response.response.insert(0, "HTTP/1.1 200 OK\r\n");
        return;
    }
    else {
        client.response.response.append(buf, bytes_read);
        memset(buf, 0, sizeof(buf));
    }
}

void WebServer::sendResponse(const int &fd, Client &client) {
    std::string msg = client.response.response;
    int bytes_sent;
    if (msg.length() >= MESSAGE_BUFFER)
        bytes_sent = send(fd, msg.c_str(), MESSAGE_BUFFER, 0);
    else
        bytes_sent = send(fd, msg.c_str(), msg.length(), 0);
    if (bytes_sent == -1) {
        closeConnection(fd);
        return;
    }
    else if (bytes_sent == 0 || (size_t)bytes_sent == msg.length()) {
        if (client.response.cgi)
            closeConnection(fd);
        else {
            FD_CLR(fd, &write_fd);
            if (fd == biggest_fd)
                --biggest_fd;
            FD_SET(fd, &recv_fd);
            if (fd > biggest_fd)
                biggest_fd = fd;
            client.response.clear();
            client.request.clear();
        }
    }
    else
        client.response.response = client.response.response.substr(bytes_sent);
}

void WebServer::runServers() {
    fd_set recv_copy;
    fd_set write_copy;
    struct timeval time;

    biggest_fd = 0;
    initSets();
    while (1) {
        time.tv_sec = 1;
        time.tv_usec = 0;
        recv_copy = recv_fd;
        write_copy = write_fd;
        if (select(biggest_fd + 1, &recv_copy, &write_copy, NULL, &time) < 0)
            continue;
        for (int i = 0; i <= biggest_fd; ++i) {
            if (FD_ISSET(i, &recv_copy) && servers_map.count(i))
                acceptNewConnection(servers_map.find(i)->second);
            else if (FD_ISSET(i, &recv_copy) && clients_map.count(i) > 0)
                readRequest(i, clients_map[i]);
            else if (FD_ISSET(i, &write_copy) && clients_map.count(i) > 0) {
                int cgi_state = clients_map[i].response.cgi;
                if (cgi_state == 1 && FD_ISSET(clients_map[i].response.cgi_resp.pipe_in[1], &write_copy))
                    sendCGIBody(clients_map[i], clients_map[i].response.cgi_resp);
                else if (cgi_state == 1 && FD_ISSET(clients_map[i].response.cgi_resp.pipe_out[0], &recv_copy))
                    readCGIResponse(clients_map[i], clients_map[i].response.cgi_resp);
                else if ((cgi_state == 0 || cgi_state == 2) && FD_ISSET(i, &write_copy))
                    sendResponse(i, clients_map[i]);
            }
        }
    }
}
