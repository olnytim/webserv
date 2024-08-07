#include "../../includes/parsing/loca.hpp"

int ft_stoi(const std::string &str) {
    int res = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] < '0' || str[i] > '9')
            throw std::exception();
        res = res * 10 + str[i] - '0';
    }
    return res;
}

// constructor, destructor, copy constructor, assignment operator
LocationBlock::LocationBlock() {
    printf("LocationBlock was created\n");
    path = "";
    root = "";
    index = "";
    return_sign = "";
    alias = "";
    autoindex = false;
    client_max_body_size = MAX_CONTENT_LENGTH;
    methods = std::vector<std::string>(5, "0");
}

LocationBlock::~LocationBlock() {
}

LocationBlock::LocationBlock(const LocationBlock &other) {
    path = other.path;
    root = other.root;
    index = other.index;
    return_sign = other.return_sign;
    alias = other.alias;
    cgi_path = other.cgi_path;
    cgi_ext = other.cgi_ext;
    methods = other.methods;
    autoindex = other.autoindex;
    client_max_body_size = other.client_max_body_size;
}

LocationBlock &LocationBlock::operator=(const LocationBlock &other) {
    if (this != &other) {
        path = other.path;
        root = other.root;
        index = other.index;
        return_sign = other.return_sign;
        alias = other.alias;
        cgi_path = other.cgi_path;
        cgi_ext = other.cgi_ext;
        methods = other.methods;
        autoindex = other.autoindex;
        client_max_body_size = other.client_max_body_size;
    }
    return (*this);
}

void LocationBlock::reportError(const ParseException &ex) const {
    throw ex;
}

// setters
void LocationBlock::setPath(const std::string &value) {
    path = value;
}

void LocationBlock::setRoot(const std::string &value) {
    root = value;
}

void LocationBlock::setIndex(const std::string &value) {
    index = value;
}

void LocationBlock::setReturn(const std::string &value) {
    return_sign = value;
}

void LocationBlock::setAlias(const std::string &value) {
    alias = value;
}

void LocationBlock::setCgiPath(const std::vector<std::string> &value) {
    cgi_path = value;
}

void LocationBlock::setCgiExt(const std::vector<std::string> &value) {
    cgi_ext = value;
}

void LocationBlock::setMethods(const std::vector<std::string> &value) {
    methods = std::vector<std::string>(5, "0");
    for (size_t i = 0; i < value.size(); i++) {
        if (value[i] == "GET")
            methods[0] = "1";
        else if (value[i] == "POST")
            methods[1] = "1";
        else if (value[i] == "DELETE")
            methods[2] = "1";
        else if (value[i] == "PUT")
            methods[3] = "1";
        else if (value[i] == "HEAD")
            methods[4] = "1";
        else
            reportError(ParseException("'" + methods[i] + "' invalid method"));
    }
}

void LocationBlock::setAutoindex(const std::string &value) {
    if (value == "on" || value == "off")
        autoindex = value == "on";
    reportError(ParseException("'" + value + "' invalid autoindex"));
}

// не уверен, что это правильно
void LocationBlock::setClientMaxBodySize(const std::string &value) {
    unsigned long   size = 0;
    size = ft_stoi(value);
    if (!size)
        reportError(ParseException("'" + value + "' invalid client_max_body_size"));
    client_max_body_size = size;
}

// getters
const std::string &LocationBlock::getPath() const {
    return path;
}

const std::string &LocationBlock::getRoot() const {
    return root;
}

const std::string &LocationBlock::getIndex() const {
    return index;
}

const std::string &LocationBlock::getReturn() const {
    return return_sign;
}

const std::string &LocationBlock::getAlias() const {
    return alias;
}

const std::vector<std::string> &LocationBlock::getCgiPath() const {
    return cgi_path;
}

const std::vector<std::string> &LocationBlock::getCgiExt() const {
    return cgi_ext;
}

const std::vector<std::string> &LocationBlock::getMethods() const {
    return methods;
}

const bool &LocationBlock::getAutoindex() const {
    return autoindex;
}

const unsigned long &LocationBlock::getClientMaxBodySize() const {
    return client_max_body_size;
}
