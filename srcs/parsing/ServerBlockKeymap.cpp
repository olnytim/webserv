#include "../../includes/parsing/ServerBlockKeymap.hpp"
#include "../../includes/parsing/ServerBlock.hpp"

void ServerBlockKeymap::callFunction(const std::string &key, const std::string &value, ServerBlock &instance) const {
    typedef void (ServerBlock::*MemberFuncType)(const std::string&);
    MemberFuncType func = keymap.find(key)->second;
    if (key.size() == 0 || value.size() == 0 || keymap.find(key) == keymap.end()) {
        errorHandler::reportError(ParseException("Invalid keyword or content for keyword in Server Block"));
    }
    (instance.*func)(value);
}

ServerBlockKeymap::ServerBlockKeymap() {
    keymap["listen"] = &ServerBlock::setPort;
    keymap["host"] = &ServerBlock::setHost;
    keymap["server_name"] = &ServerBlock::setServerName;
    keymap["root"] = &ServerBlock::setRoot;
    keymap["index"] = &ServerBlock::setIndex;
    keymap["client_max_body_size"] = &ServerBlock::setClientMaxBodySize;
    keymap["autoindex"] = &ServerBlock::setAutoindex;
    keymap["error_page"] = &ServerBlock::setErrorPages;
}