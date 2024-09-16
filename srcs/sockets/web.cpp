#include "../../includes/sockets/web.hpp"

WebServer::WebServer() {
//    FD_ZERO(&recv_fd);
//    FD_ZERO(&write_fd);
//    biggest_fd = 0;
}

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
//    std::vector<ServerBlock>::iterator it;
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
    close(fd);
    FD_CLR(fd, &recv_fd);
    if (fd == biggest_fd)
        --biggest_fd;
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
    printf("clients_map size: %lu\n", clients_map.size());
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

void WebServer::readRequest(const int &fd, Client &client) {
    char buf[MESSAGE_BUFFER];
    int bytes_read;
    bytes_read = recv(fd, buf, sizeof(buf), 0);

    if (bytes_read == -1) {
        printf("Recv error\n");
        closeConnection(fd);
        return;
    }
    else if (bytes_read == 0) {
        printf("Connection closed\n");
        closeConnection(fd);
        return;
    }
    else {
        client.request.reqParse(buf, bytes_read); // здесь пока остановился. до этого вроде всё работает
        memset(buf, 0, sizeof(buf));
    }
    assignServer(client);
    client.response.request = client.request;
    printf("enum method: %d\n", client.request.method);
    client.response.createResponse();
    FD_SET(fd, &write_fd);
    if (fd == biggest_fd)
        --biggest_fd;
    FD_SET(fd, &write_fd);
    if (fd > biggest_fd)
        biggest_fd = fd;
}

void WebServer::sendResponse(const int &fd, Client &client) {
    int bytes_sent;
    bytes_sent = send(fd, client.response.response.c_str(), client.response.response.length(), 0);
    printf("\n\nResponse: %s\n\n", client.response.response.c_str());
    if (bytes_sent == -1) {
        printf("Send error\n");
        closeConnection(fd);
        return;
    }
    else if (bytes_sent == 0) {
        printf("Connection closed\n");
        closeConnection(fd);
        return;
    }
    else {
        FD_CLR(fd, &write_fd);
        if (fd == biggest_fd)
            --biggest_fd;
        closeConnection(fd);
    }
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
        if (select(biggest_fd + 1, &recv_copy, &write_copy, NULL, &time) < 0) {
            printf("Select error\n");
            exit(1);
        }
        for (int i = 0; i <= biggest_fd; ++i) {
            if (FD_ISSET(i, &recv_copy) && servers_map.count(i)) {
                acceptNewConnection(servers_map.find(i)->second);
            }
            else if (FD_ISSET(i, &recv_copy) && clients_map.count(i) > 0) {
                readRequest(i, clients_map[i]);
            }
            else if (FD_ISSET(i, &write_copy) && clients_map.count(i) > 0) {
                sendResponse(i, clients_map[i]);
            }
        }
    }
}
