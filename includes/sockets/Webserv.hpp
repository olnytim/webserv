#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "../parsing/ServerBlock.hpp"
#include "../parsing/LocationBlock.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>

class Webserv {
    ServerBlock server_config;
    unsigned short port;
    int server_fd;

public:
    Webserv(ServerBlock server_config);

};

#endif //WEBSERV_HPP
