#pragma once

#include "ServerBlockKeymap.hpp"
#include "../Headers.hpp"
#include "LocationBlock.hpp"

class ServerBlock {
private:
    int                         port;
    int                         listen_fd;
    in_addr_t                   host;
    std::string                 server_name;
    std::string                 root;
    std::string                 index;
    unsigned long               client_max_body_size;
    bool                        autoindex;
    std::map<int, std::string>  error_pages;
    std::vector<LocationBlock>  locations;
    struct sockaddr_in          server_address;
    ServerBlockKeymap           keymap;
public:
    // constructor, destructor, copy constructor, assignment operator
    ServerBlock();
    ~ServerBlock();

    ServerBlock(const ServerBlock &other);
    ServerBlock &operator=(const ServerBlock &other);

    // methods
    bool isValidHost(const std::string &host) const;
    void setupServer();

    // setters
    void setPort(const std::string &value);
    void setFd(const std::string &value);
    void setFd(int value);
    void setHost(const std::string &value);
    void setServerName(const std::string &value);
    void setRoot(const std::string &value);
    void setIndex(const std::string &value);
    void setClientMaxBodySize(const std::string &value);
    void setAutoindex(const std::string &value);
    void setErrorPages(const std::string &value);
    void setLocations(const std::vector<LocationBlock> & locaVector);

    // getters
    ServerBlockKeymap   getKeymap() const;
    const int           &getPort() const;
    const int           &getFd() const;
    const in_addr_t     &getHost() const;
    const std::string   &getServerName() const;
    const std::string   &getRoot() const;
    const std::string   &getIndex() const;
    const unsigned long &getClientMaxBodySize() const;
    const bool          &getAutoindex() const;
    const std::map<int, std::string>    &getErrorPages() const;
    const std::vector<LocationBlock>    &getLocations() const;
    const struct sockaddr_in            &getServerAddress() const;
    std::vector<LocationBlock>::iterator   getLocationKey(std::string key);
};
