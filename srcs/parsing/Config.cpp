#include "../../includes/parsing/Config.hpp"
#include "../../includes/parsing/blockPrinter.hpp"


Config::Config() {}

Config::~Config() {}

// opening config file
int Config::getTypePath(const std::string &path) {
    struct stat sb = {};
    if (stat(path.c_str(), &sb) == 0) {
        if (S_ISREG(sb.st_mode))
            return 1;
        else if (S_ISDIR(sb.st_mode))
            return 2;
        else
            return 3;
    }
    return 0;
}

std::string Config::getContent(const std::string &path) {
    if (path.empty())
        return "";
    std::ifstream file(path.c_str());
    if (!file.is_open() || !file)
        return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


const std::string &Config::getFile() const {
    return conf_file;
}

const std::vector<ServerBlock> &Config::getServers() const {
    return servers;
}

bool Config::isFileExistAndReadable(const std::string &path, const std::string &index) {
    if (getTypePath(index) == 1 && access(index.c_str(), R_OK) == 0)
        return true;
    if (getTypePath(path + index) == 1 && access((path + index).c_str(), R_OK) == 0)
        return true;
    return false;
}

void Config::parseConfig(std::string &content) {
    // remove comments
    size_t start_pos = 0;
    while ((start_pos = content.find('#', start_pos)) != std::string::npos) {
        size_t end_pos = content.find('\n', start_pos);
        if (end_pos == std::string::npos)
            content.erase(start_pos);
        else
            content.erase(start_pos, end_pos - start_pos);
    }
    // remove whitespaces
    start_pos = content.find_first_not_of(" \t\n\r\f\v");
    if (start_pos == std::string::npos) {
        content.clear();
        return;
    }
    size_t end_pos = content.find_last_not_of(" \t\n\r\f\v");
    content = content.substr(start_pos, end_pos - start_pos + 1);
}

void Config::splitServers(std::string &content) {
    size_t opening_bracket_pos = 0;
    size_t end_pos = 0;
    size_t server_pos = 0;

    while (end_pos != content.length() - 1) {
        server_pos = content.find("server");
        if (server_pos == std::string::npos)
            break;
        opening_bracket_pos = parsingUtils::SkipWhitespaces(content, server_pos + 6);
        if (opening_bracket_pos == std::string::npos || content[opening_bracket_pos] != '{')
            errorHandler::reportError(ParseException("Server block is not opened or has invalid format"));
        end_pos = parsingUtils::findEndingBracket(content, opening_bracket_pos + 1);
        if (end_pos == std::string::npos)
            errorHandler::reportError(ParseException("Server or location block is not closed"));
        server_config.push_back(content.substr(opening_bracket_pos + 1, end_pos - opening_bracket_pos - 1));
        content = content.substr(0, server_pos) + content.substr(end_pos + 1);
    }
    content = parsingUtils::trimWhitespace(content);
    if (!content.empty() || server_config.empty())
        errorHandler::reportError(ParseException("Invalid server block"));
}

std::vector<std::string> Config::SplitAndCutLocations(std::string &config) const{
    size_t current_pos = 0;
    size_t end_pos = 0;
    std::vector<std::string> locations;

    while (current_pos != std::string::npos) {
        current_pos = config.find("location");
        if (current_pos == std::string::npos)
            break;
        size_t opening_bracket_pos = config.find('{', current_pos);
        if (opening_bracket_pos == std::string::npos)
            errorHandler::reportError(ParseException("Location block is not opened"));
        end_pos = parsingUtils::findEndingBracket(config, opening_bracket_pos + 1);
        if (end_pos == std::string::npos)
            errorHandler::reportError(ParseException("Server or location block is not closed"));
        locations.push_back(config.substr(current_pos + 8, end_pos - current_pos - 8));
        config = config.substr(0, current_pos) + config.substr(end_pos + 1);
        current_pos = end_pos + 1;
    }
    return locations;
}

LocationBlock Config::CreateLocation(std::string &locationTxt) const {
    LocationBlock location;
    std::string path = locationTxt.substr(0, locationTxt.find('{'));
    path = parsingUtils::trimWhitespace(path);
    location.setPath(path);
    locationTxt = locationTxt.substr(locationTxt.find('{') + 1);
    locationTxt = parsingUtils::trimWhitespace(locationTxt);
    std::vector<std::string> params = parsingUtils::splitParams(locationTxt, ";");

    for (size_t i = 0; i < params.size(); i++) {
        params[i] = parsingUtils::trimWhitespace(params[i]);
        std::string key = params[i].substr(0, params[i].find(' '));
        std::string value = params[i].substr(params[i].find(' ') + 1);
        key = parsingUtils::trimWhitespace(key);
        value = parsingUtils::trimWhitespace(value);
        location.getKeymap().callFunction(key, value, location);
    }
    return location;
}

std::vector<LocationBlock> Config::ParseConfigLocations(std::string &config) const {
    std::vector<std::string> locationsTxt = SplitAndCutLocations(config);
    std::vector<LocationBlock> locationBlocks;
    for (size_t i = 0; i < locationsTxt.size(); i++) {
        locationBlocks.push_back(CreateLocation(locationsTxt[i]));
    }
    return locationBlocks;
}

ServerBlock Config::createServer(std::string &serverTxt) const {
    ServerBlock server;
    server.setLocations(ParseConfigLocations(serverTxt));
    serverTxt = parsingUtils::trimWhitespace(serverTxt);
    std::vector<std::string> params = parsingUtils::splitParams(serverTxt, std::string(";"));
    for (size_t i = 0; i < params.size(); i++) {
        params[i] = parsingUtils::trimWhitespace(params[i]);
        std::string key = params[i].substr(0, params[i].find(' '));
        std::string value = params[i].substr(params[i].find(' ') + 1);
        key = parsingUtils::trimWhitespace(key);
        value = parsingUtils::trimWhitespace(value);
        server.getKeymap().callFunction(key, value, server);
    }
    if (server.getRoot().empty())
        server.setRoot("/");
    if (server.getHost() == 0)
        server.setHost("localhost");
    if (server.getIndex().empty())
        server.setIndex("index.html");
    return server;
}

void Config::createCluster(const std::string &config_file) {
    // проверка корректности файла
    conf_file = config_file;
    std::string content = getContent(config_file);
    if (content.empty())
        errorHandler::reportError(ParseException(config_file + " is empty"));
    if (access(config_file.c_str(), R_OK) != 0)
        errorHandler::reportError(ParseException("Can't read file " + config_file));
    if (getTypePath(config_file) != 1)
        errorHandler::reportError(ParseException("File " + config_file + " is not a regular file"));

    // парсинг конфига
    parseConfig(content);
    splitServers(content);

    // создание серверов и готово кластера
    for (size_t i = 0; i < server_config.size(); ++i) {
        ServerBlock server = createServer(server_config[i]);
        servers.push_back(server);
    }
    parsingValidator::validateServers(servers);
}
