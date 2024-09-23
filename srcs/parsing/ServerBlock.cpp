#include "../../includes/parsing/ServerBlock.hpp"

ServerBlock::ServerBlock() {
    host = 0;
    port = 0;
    listen_fd = 0;
    server_name = "";
    root = "";
    index = "";
    client_max_body_size = MAX_CONTENT_LENGTH;
    autoindex = false;
 	keymap = ServerBlockKeymap();
    error_pages = std::map<int, std::string>();
}

ServerBlock::~ServerBlock() {
}

ServerBlockKeymap ServerBlock::getKeymap() const {
    return keymap;
}

ServerBlock::ServerBlock(const ServerBlock &other) {
    port = other.port;
    listen_fd = other.listen_fd;
    host = other.host;
    server_name = other.server_name;
    root = other.root;
    index = other.index;
    client_max_body_size = other.client_max_body_size;
    autoindex = other.autoindex;
    error_pages = other.error_pages;
    locations = other.locations;
    server_address = other.server_address;
    keymap = other.keymap;
}

ServerBlock &ServerBlock::operator=(const ServerBlock &other) {
    if (this != &other) {
        port = other.port;
        listen_fd = other.listen_fd;
        host = other.host;
        server_name = other.server_name;
        root = other.root;
        index = other.index;
        client_max_body_size = other.client_max_body_size;
        autoindex = other.autoindex;
        error_pages = other.error_pages;
        locations = other.locations;
        server_address = other.server_address;
		keymap = other.keymap;
    }
    return (*this);
}

bool ServerBlock::isValidHost(const std::string &host) const {
    struct sockaddr_in sockaddr;
    return inet_pton(AF_INET, host.c_str(), &(sockaddr.sin_addr)) != 0;
}

void ServerBlock::setupServer() {
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        errorHandler::reportError(ParseException("Socket creation failed"));
    int value = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = host;
    if (bind(listen_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        errorHandler::reportError(ParseException("Bind failed"));
}

// setters
void ServerBlock::setPort(const std::string &value) {
    port = parsingUtils::ft_stoi(value);
    if (port < 0 || port > 65535)
        errorHandler::reportError(ParseException("Invalid port"));
}

void ServerBlock::setLocations(const std::vector<LocationBlock> &locaVector) {
    locations = locaVector;
}

void ServerBlock::setFd(const std::string &value) {
    try {
        int listen = parsingUtils::ft_stoi(value);
        if (listen < 0 || listen > 65535)
            errorHandler::reportError(ParseException("'" + value + "' invalid listen"));
        listen_fd = listen;
    } catch (std::exception &) {
        errorHandler::reportError(ParseException("'" + value + "' invalid listen"));
    }

}

void ServerBlock::setFd(int value) {
    listen_fd = value;
}

void ServerBlock::setHost(const std::string &value) {
    std::string hostStr = value;
    if (value == "localhost")
        hostStr = "127.0.0.1";
    if (!isValidHost(value))
        errorHandler::reportError(ParseException("'" + hostStr + "' invalid host"));
    this->host = inet_addr(value.c_str());
    if (this->host == INADDR_NONE)
        errorHandler::reportError(ParseException( "'" + hostStr + "' invalid host"));
}

void ServerBlock::setServerName(const std::string &value) {
    server_name = value;
}

// возможно, нужно будет улучшить
void ServerBlock::setRoot(const std::string &value) {
    root = value;
}

void ServerBlock::setIndex(const std::string &value) {
    index = value;
}

void ServerBlock::setClientMaxBodySize(const std::string &value) {
    unsigned long   size = 0;
    try {
        size = parsingUtils::ft_stoi(value);
    } catch (std::exception &) {
        errorHandler::reportError(ParseException("'" + value + "' invalid client_max_body_size"));
    }
    client_max_body_size = size;
}

void ServerBlock::setAutoindex(const std::string &value) {
    if (value == "on" || value == "off")
        autoindex = value == "on";
    errorHandler::reportError(ParseException("'" + value + "' invalid autoindex"));
}

void ServerBlock::setErrorPages(const std::string &value) {
    std::vector<std::string> params = parsingUtils::splitParams(value, " ");
    if (params.size() < 2)
        errorHandler::reportError(ParseException("Invalid error_page"));
    std::vector<std::string>::iterator it = params.begin();
    std::vector<std::string>::iterator error_page = params.end() - 1;
    while (it != params.end() - 1) {
        try {
            int code = parsingUtils::ft_stoi(*it);
            if (code < 100 || code > 599)
                errorHandler::reportError(ParseException("Invalid error code"));
            error_pages[code] = *error_page;
        }
        catch (std::exception &) {
            errorHandler::reportError(ParseException("Invalid error code"));
        }
        ++it;
    }
}

// getters

const int &ServerBlock::getPort() const {
    return port;
}

const int &ServerBlock::getFd() const {
    return listen_fd;
}

const in_addr_t &ServerBlock::getHost() const {
    return host;
}

const std::string &ServerBlock::getServerName() const {
    return server_name;
}

const std::string &ServerBlock::getRoot() const {
    return root;
}

const std::string &ServerBlock::getIndex() const {
    return index;
}

const unsigned long &ServerBlock::getClientMaxBodySize() const {
    return client_max_body_size;
}

const bool &ServerBlock::getAutoindex() const {
    return autoindex;
}

const std::map<int, std::string> &ServerBlock::getErrorPages() const {
    return error_pages;
}

const std::vector<LocationBlock> &ServerBlock::getLocations() const {
    return locations;
}

const struct sockaddr_in &ServerBlock::getServerAddress() const {
    return server_address;
}

const std::vector<LocationBlock>::iterator ServerBlock::getLocationKey(std::string key)
{
    std::vector<LocationBlock>::iterator it;
    for (it = this->locations.begin(); it != this->locations.end(); it++)
        if (it->getPath() == key)
            return it;
    throw std::runtime_error("Location not found");
}