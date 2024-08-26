#include "../../includes/parsing/serve.hpp"

ServerBlock::ServerBlock() {
    printf("ServerBlock was created\n");
    port = 0;
    listen_fd = 0;
    host = 0;
    server_name = "";
    root = "";
    index = "";
    client_max_body_size = MAX_CONTENT_LENGTH;
    autoindex = false;
    // error_pages;
}

ServerBlock::~ServerBlock() {
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
    }
    return (*this);
}

// methods
void ServerBlock::reportError(const ParseException &ex) const {
    throw ex;
}

void ServerBlock::checkToken(std::string &parametr)
{
    size_t pos = parametr.rfind(';');
    if (pos != parametr.size() - 1)
        reportError(ParseException("';' expected"));
    parametr.erase(pos);
}

bool ServerBlock::isValidHost(const std::string &host) const {
    struct sockaddr_in sockaddr;
    return inet_pton(AF_INET, host.c_str(), &(sockaddr.sin_addr)) != 0;
}

void ServerBlock::setupServer() {
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        reportError(ParseException("Socket creation failed"));
    int value = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = host;
    if (bind(listen_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        reportError(ParseException("Bind failed"));
}

// setters
void ServerBlock::setPort(std::string value) {
    checkToken(value);
    port = ft_stoi(value);
    if (port < 0 || port > 65535)
        reportError(ParseException("Invalid port"));
}

void ServerBlock::setFd(int value) {
    listen_fd = value;
}

void ServerBlock::setHost(std::string value) {
    checkToken(value);
    if (value == "localhost")
        value = "127.0.0.1";
    if (!isValidHost(value))
        reportError(ParseException("'" + value + "' invalid host"));
    host = inet_addr(value.c_str());
    if (host == INADDR_NONE)
        reportError(ParseException( "'" + value + "' invalid host"));
}

void ServerBlock::setServerName(std::string value) {
    checkToken(value);
    server_name = value;
}

// возможно, нужно будет улучшить
void ServerBlock::setRoot(std::string value) {
    checkToken(value);
    root = value;
}

void ServerBlock::setIndex(std::string value) {
    checkToken(value);
    index = value;
}

void ServerBlock::setClientMaxBodySize(std::string value) {
    checkToken(value);
    unsigned long   size = 0;
    size = ft_stoi(value);
    if (!size)
        reportError(ParseException("'" + value + "' invalid client_max_body_size"));
    client_max_body_size = size;
}

void ServerBlock::setAutoindex(std::string value) {
    checkToken(value);
    if (value == "on" || value == "off")
        autoindex = value == "on";
    reportError(ParseException("'" + value + "' invalid autoindex"));
}

// void ServerBlock::setErrorPages(std::vector<std::string> &value) {
// }

// void ServerBlock::addLocation(std::string name, std::vector<std::string> &value) {
// }

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

void ServerBlock::print() const {
    printf("ServerBlock:\n");
    printf("port: %d\n", port);
    printf("listen_fd: %d\n", listen_fd);
    printf("host: %d\n", host);
    printf("server_name: %s\n", server_name.c_str());
    printf("root: %s\n", root.c_str());
    printf("index: %s\n", index.c_str());
    printf("client_max_body_size: %lu\n", client_max_body_size);
    printf("autoindex: %d\n", autoindex);
    printf("error_pages: \n");
    printf("locations: \n");
    printf("server_address: \n");

    locations[0].print();
}

std::vector<LocationBlock>::iterator ServerBlock::getLocationKey(std::string key)
{
    std::vector<LocationBlock>::iterator it;
    for (it = this->locations.begin(); it != this->locations.end(); it++) {
        if (it->getPath() == key)
            return it;
    }
    throw std::runtime_error("Location not found");
}
