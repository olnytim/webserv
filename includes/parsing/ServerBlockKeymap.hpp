#ifndef SERVERBLOCKKEYMAP_HPP
#define SERVERBLOCKKEYMAP_HPP

#include "../Headers.hpp"

class ServerBlock;

class ServerBlockKeymap {
public:
    void callFunction(const std::string &key, const std::string &value, ServerBlock &instance) const;
    ServerBlockKeymap();
private:
    typedef void(ServerBlock::*func)(const std::string&);
    std::map<std::string, func> keymap;
};

#endif //SERVERBLOCKKEYMAP_HPP
