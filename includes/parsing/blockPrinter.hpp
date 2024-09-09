//
// Created by ashot on 9/8/2024.
//

#ifndef BLOCKPRINTER_HPP
#define BLOCKPRINTER_HPP
#include "Config.hpp"

class block_printer {
    static void print(const LocationBlock &location) {
        std::cout << "name location: " << location.getPath() << std::endl;
        //std::cout << "methods: " << itl->getPrintMethods() << std::endl;
        //std::cout << "index: " << itl->getIndexLocation() << std::endl;
        if (location.getCgiPath().empty())
        {
            //std::cout << "root: " << itl->getRootLocation() << std::endl;
            if (!location.getReturn().empty())
                std::cout << "return: " << location.getReturn() << std::endl;
            if (!location.getAlias().empty())
                std::cout << "alias: " << location.getAlias() << std::endl;
        }
        else
        {
            //std::cout << "cgi root: " << itl->getRootLocation() << std::endl;
            std::cout << "cgi_path: " << itl->getCgiPath().size() << std::endl;
            //std::cout << "cgi_ext: " << itl->getCgiExtension().size() << std::endl;
        }
    }

    static void print(const ServerBlock &server) {
            std::cout << "Server name: " << server.getServerName() << std::endl;
            std::cout << "Host: " << server.getHost() << std::endl;
            std::cout << "Root: " << server.getRoot() << std::endl;
            std::cout << "Index: " << server.getIndex() << std::endl;
            std::cout << "Port: " << server.getPort() << std::endl;
            std::cout << "Max BSize: " << server.getClientMaxBodySize() << std::endl;
            std::cout << "Error pages: " << server.getErrorPages().size() << std::endl;
            //std::map<short, std::string>::const_iterator it = server.getErrorPages().begin();
            //while (it != server.getErrorPages().end())
            //{
            //    std::cout << (*it).first << " - " << it->second << std::endl;
            //    ++it;
            //}
            std::cout << "Locations: " << server.getLocations().size() << std::endl;
            std::vector<LocationBlock>::const_iterator itl = server.getLocations().begin();
            while (itl != server.getLocations().end())
            {
                print(*itl);
                ++itl;
            }
            itl = servers[i].getLocations().begin();

    }

    static void print(const Config &config) {
        std::cout << "------------- Config -------------" << std::endl;
        for (size_t i = 0; i < servers.size(); i++)
        {
            std::cout << "Server #" << i + 1 << std::endl;
            print (servers[i]);
            std::cout << "-----------------------------" << std::endl;
        }
    }
};

#endif //BLOCKPRINTER_HPP
