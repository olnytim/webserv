#pragma once

#include "../Headers.hpp"
#include "../parsing/serve.hpp"
#include "cli.hpp"

class WebServer {
private:
    std::vector<ServerBlock> servers;
    std::map<int, ServerBlock> servers_map;
    std::map<int, Client> clients_map;

    fd_set recv_fd;
    fd_set write_fd;
    int biggest_fd;

public:
    WebServer();
    ~WebServer();

    void setupServers(std::vector<ServerBlock> prep_servers);

    void addToSet(int fd, fd_set &set);
    void removeFromSet(int fd, fd_set &set);
    void acceptNewConnection(ServerBlock &server);
    void readRequest(const int &fd, Client &client);

    void initSets();
    void closeConnection(const int fd);
    void runServers();
};