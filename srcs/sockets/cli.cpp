#include "../../includes/sockets/cli.hpp"

Client::Client() {
    client_fd = -1;
}

Client::~Client() {}

Client::Client(ServerBlock &server) {
    client_fd = -1;
    response.server = server;
}

Client::Client(const Client &other) {
    if (this != &other) {
        client_fd = other.client_fd;
        client_addr = other.client_addr;
        request = other.request; // доработать в cli.hpp и cli.cpp
        response = other.response;
        server = other.server;
    }
}

Client &Client::operator=(const Client &other) {
    if (this != &other) {
        client_fd = other.client_fd;
        client_addr = other.client_addr;
        request = other.request; // доработать в cli.hpp и cli.cpp
        response = other.response;
        server = other.server;
    }
    return (*this);
}

