#include <csignal>
#include "../../includes/sockets/Webserv.hpp"

Webserv::Webserv(ServerBlock server_config) : server_config(server_config) {
    port = server_config.getPort();
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        throw std::runtime_error("Failed to create socket");
    }
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
        throw std::runtime_error("Failed to set socket options");
    }
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        throw std::runtime_error("Failed to bind socket");
    }
    if (listen(server_fd, 3) == -1) {
        throw std::runtime_error("Failed to listen on socket");
    }
}

void Webserv::accept_connections() {
    int addrlen = sizeof(address);
    int client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (client_fd == -1) {
        throw std::runtime_error("Failed to accept connection");
    }
    handle_request(client_fd);
}

void Webserv::handle_request(int client_fd) {
    char buffer[2048] = {0};
    int valread = read(client_fd, buffer, 2048);
    if (valread == -1) {
        throw std::runtime_error("Failed to read from socket");
    }
    std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    send_response(client_fd, response);
}

void Webserv::send_response(int client_fd, std::string response) {
    send(client_fd, response.c_str(), response.length(), 0);
}

void Webserv::run() {
    while (true) {
        accept_connections();
    }
}
