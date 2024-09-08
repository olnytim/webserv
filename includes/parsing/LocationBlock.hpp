#pragma once

#include "../Headers.hpp"
#include "LocationBlockKeymap.hpp"
#include "errorHandler.hpp"

class LocationBlock {
private:
    std::string path;
    std::string root;
    std::string index;
    std::string return_sign;
    std::string alias;
    std::vector <std::string> cgi_path;
    std::vector <std::string> cgi_ext;
    std::vector <std::string> methods;
    bool autoindex;
    unsigned long client_max_body_size;

    LocationBlockKeymap keymap;
public:
    // constructor, destructor, copy constructor, assignment operator
    LocationBlock();
    ~LocationBlock();
    LocationBlock(const LocationBlock &other);
    LocationBlock &operator=(const LocationBlock &other);

    // setters
    void setPath(const std::string &value);
    void setRoot(const std::string &value);
    void setIndex(const std::string &value);
    void setReturn(const std::string &value);
    void setAlias(const std::string &value);
    void setCgiPath(const std::vector<std::string> &value);
    void setCgiPath(const std::string &value);
    void setCgiExt(const std::vector<std::string> &value);
    void setCgiExt(const std::string &value);
    void setMethods(const std::vector<std::string> &value);
    void setMethods(const std::string &value);
    void setAutoindex(const std::string &value);
    void setClientMaxBodySize(const std::string &value);

    // getters
    const std::string &getPath() const;
    const std::string &getRoot() const;
    const std::string &getIndex() const;
    const std::string &getReturn() const;
    const std::string &getAlias() const;
    const std::vector<std::string> &getCgiPath() const;
    const std::vector<std::string> &getCgiExt() const;
    const std::vector<std::string> &getMethods() const;
    const LocationBlockKeymap &getKeymap() const;
    const bool &getAutoindex() const;
    const unsigned long &getClientMaxBodySize() const;

};
