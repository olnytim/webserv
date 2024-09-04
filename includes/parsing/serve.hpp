#pragma once

#include "ServerBlockKeymap.hpp"
#include "../Headers.hpp"
#include "loca.hpp"
#include "exceptions.hpp"

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

    void setLocations(const std::vector<LocationBlock> & vector);

    ServerBlockKeymap getKeymap() const;

    ServerBlock(const ServerBlock &other);
    ServerBlock &operator=(const ServerBlock &other);

    // exceptions
    void reportError(const ParseException &ex) const;

    // methods
    void checkToken(const std::string &value);
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
    void addLocation(std::string name, std::vector<std::string> &value);

    // getters
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

    void print() const;
};
