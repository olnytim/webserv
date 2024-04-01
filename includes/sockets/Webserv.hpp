#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "../parsing/ServerBlock.hpp"
#include "../parsing/LocationBlock.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Webserv {
    ServerBlock server_config;
    unsigned short port;
    int server_fd;
    struct sockaddr address;
    vector<ServerBlock> servers;
//    struct sockaddr_in &address_in = reinterpret_cast<struct sockaddr_in &>(address);

public:
    Webserv(ServerBlock server_config);

    void accept_connections();
    void handle_request(int client_fd);
    void send_response(int client_fd, std::string response);
    void run();

};

#endif //WEBSERV_HPP
