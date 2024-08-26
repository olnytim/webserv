#pragma once

#include "../Headers.hpp"
//#include "../parsing/serve.hpp"
#include "req.hpp"
#include "res.hpp"

class Client {
public:
    int client_fd;
    struct sockaddr_in client_addr;

    Request request; // доработать в cli.hpp и cli.cpp
    Response response;
    ServerBlock server;

    Client();
    ~Client();
    Client(ServerBlock &server);
    Client(const Client &other);
    Client &operator=(const Client &other);

};