#include "../../includes/parsing/LocationBlockKeymap.hpp"
#include "../../includes/parsing/exceptions.hpp"
#include "../../includes/parsing/LocationBlock.hpp"

LocationBlockKeymap::LocationBlockKeymap(){
    keymap["root"] = &LocationBlock::setRoot;
    keymap["index"] = &LocationBlock::setIndex;
    keymap["return"] = &LocationBlock::setReturn;
    keymap["alias"] = &LocationBlock::setAlias;
    keymap["cgi_path"] = &LocationBlock::setCgiPath;
    keymap["cgi_ext"] = &LocationBlock::setCgiExt;
    keymap["methods"] = &LocationBlock::setMethods;
    keymap["autoindex"] = &LocationBlock::setAutoindex;
    keymap["client_max_body_size"] = &LocationBlock::setClientMaxBodySize;
}

void LocationBlockKeymap::callFunction(std::string key, const std::string &value, LocationBlock &instance) const
{
    typedef void (LocationBlock::*MemberFuncType)(const std::string&);
    MemberFuncType func = keymap.find(key)->second;
    if (key.size() == 0 || value.size() == 0 || !func){
        errorHandler::reportError(locationParseException("Invalid keyword or content for keyword in Location Block"));
    }
    (instance.*func)(value);
}