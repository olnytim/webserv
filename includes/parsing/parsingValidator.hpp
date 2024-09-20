#ifndef PARSINGVALIDATOR_HPP
#define PARSINGVALIDATOR_HPP

// #include "../Headers.hpp"
#include "ServerBlock.hpp"
#include <algorithm>

class parsingValidator {
public:
    static void validateServers(const std::vector<ServerBlock> &servers) {
        std::vector<std::string> server_names;
        std::vector<int> server_ports;

        for (size_t i = 0; i < servers.size(); i++) {
            const std::string& server_name = servers[i].getServerName();
            int port = servers[i].getPort();

            if (std::find(server_names.begin(), server_names.end(), server_name) != server_names.end() &&
                std::find(server_ports.begin(), server_ports.end(), port) != server_ports.end()) {
                throw ParseException("Duplicate Servers");
                }
            server_names.push_back(server_name);
            server_ports.push_back(port);
        }
    }
};

#endif //PARSINGVALIDATOR_HPP
