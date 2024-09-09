#pragma once

#include "../Headers.hpp"

class LocationBlock;

class LocationBlockKeymap{
public:
    void callFunction(std::string key, const std::string &value, LocationBlock &instance) const;
    LocationBlockKeymap();
private:
    typedef void(LocationBlock::*func)(const std::string&);
    std::map<std::string, func> keymap;
};