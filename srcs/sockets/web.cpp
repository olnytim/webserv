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
    Client client;
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

void WebServer::readRequest(const int &fd, Client &client) {
    char buf[MESSAGE_BUFFER];
    std::string msg;
    int bytes_read;
    bytes_read = recv(fd, buf, sizeof(buf), 0);

    msg = read(open("www/index.html", O_RDONLY), buf, bytes_read);
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
        (void)client;
        printf("Request: %s\n", buf);
//        client.request.feed(buf, bytes_read); // здесь пока остановился. до этого вроде всё работает
//        client.response.sendResponse(fd, msg.c_str());
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
                printf("New connection\n");
            }
            else if (FD_ISSET(i, &recv_copy) && clients_map.count(i) > 0) {
                readRequest(i, clients_map[i]);
                printf("Read request\n");
            }
//            else if (FD_ISSET(i, &write_copy) && clients_map.count(i) > 0) {
//                printf("Send response\n");
//            }
        }
    }
}
