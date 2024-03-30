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