#include "../../includes/parsing/LocationBlock.hpp"
#include "../../includes/parsing/parsingUtils.hpp"

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
    keymap = LocationBlockKeymap();
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
    keymap = other.getKeymap();
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
        keymap = other.getKeymap();
    }
    return (*this);
}

LocationBlock::~LocationBlock() {
}
//

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

void LocationBlock::setCgiPath(const std::string &value) {
    std::vector<std::string> paths = parsingUtils::splitParams(value, " ");
    setCgiPath(paths);
}

void LocationBlock::setCgiExt(const std::vector<std::string> &value) {
    cgi_ext = value;
}

void LocationBlock::setCgiExt(const std::string &value) {
    std::vector<std::string> exits = parsingUtils::splitParams(value, " ");
    setCgiExt(exits);
}

void LocationBlock::setAutoindex(const std::string &value) {
    if (value == "on" || value == "off")
        autoindex = value == "on";
    errorHandler::reportError(ParseException("'" + value + "' invalid autoindex"));
}

void LocationBlock::setClientMaxBodySize(const std::string &value) {
    unsigned long   size = 0;
    if (value == "0") {
        client_max_body_size = 0;
        return;
    }
    std::istringstream(value) >> size;
    if (size == 0)
        errorHandler::reportError(ParseException("'" + value + "' invalid client_max_body_size"));
    client_max_body_size = size;
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
            errorHandler::reportError(ParseException("'" + methods[i] + "' invalid method"));
    }
}

void LocationBlock::setMethods(const std::string &value) {
    std::vector<std::string> methods = parsingUtils::splitParams(value, " ");
    setMethods(methods);
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

const LocationBlockKeymap & LocationBlock::getKeymap() const {
    return keymap;
}

const bool &LocationBlock::getAutoindex() const {
    return autoindex;
}

const unsigned long &LocationBlock::getClientMaxBodySize() const {
    return client_max_body_size;
}
