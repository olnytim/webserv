#ifndef PARSINGVALIDATOR_HPP
#define PARSINGVALIDATOR_HPP

// #include "../Headers.hpp"
#include "ServerBlock.hpp"
#include <algorithm>

class parsingValidator {
public:

    static void validateErrorPages(const std::string &root, const std::map<int, std::string> &error_pages) {
        if (error_pages.size() == 0)
            return;
        for (std::map<int, std::string>::const_iterator it = error_pages.begin(); it != error_pages.end(); it++) {
            if (it->first < 400 || it->first > 599) {
                throw ValidationException("Invalid error code");
            }
            std::string path = root + it->second;
            std::fstream page(path.c_str());
            if (!page.good()) {
                throw ValidationException("Invalid error page");
            }
        }
    }

    static void validateLocations(const std::vector<LocationBlock> &locations) {
        std::vector<std::string> paths;

        for (size_t i = 0; i < locations.size(); i++) {
            if (std::find(paths.begin(), paths.end(), locations[i].getPath()) != paths.end()) {
                throw ValidationException("Duplicate Location paths");
            }
            paths.push_back(locations[i].getPath());
        }
    }

    static void validateServers(const std::vector<ServerBlock> &servers) {
        std::vector<std::string> server_names;
        std::vector<int> server_ports;


        for (size_t i = 0; i < servers.size(); i++) {
            const std::string& server_name = servers[i].getServerName();
            int port = servers[i].getPort();

            if (std::find(server_names.begin(), server_names.end(), server_name) != server_names.end() &&
                std::find(server_ports.begin(), server_ports.end(), port) != server_ports.end()) {
                throw ValidationException("Duplicate Servers");
                }
            validateLocations(servers[i].getLocations());
            validateErrorPages(servers[i].getRoot(), servers[i].getErrorPages());
            server_names.push_back(server_name);
            server_ports.push_back(port);
        }
    }
};

#endif //PARSINGVALIDATOR_HPP
