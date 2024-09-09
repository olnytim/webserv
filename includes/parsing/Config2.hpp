#pragma once

#include "../Headers.hpp"
#include "exceptions.hpp"
#include "ServerBlock.hpp"
#include "parsingUtils.hpp"

class Config {
private:
    std::vector<ServerBlock>    servers;
    std::vector<std::string>    server_config;
    std::string                 conf_file;
public:
    Config();
    ~Config();

    static int getTypePath(const std::string &path);
    static std::string getContent(const std::string &path);
    static bool isFileExistAndReadable(const std::string &path, const std::string &index);

    const std::string &getFile() const;
    const std::vector<ServerBlock> &getServers() const;

    static void parseConfig(std::string &content);
    void splitServers(const std::string &content);
    std::vector<LocationBlock> ParseConfigLocations(std::string &config) const;
    std::vector<std::string> SplitAndCutLocations(std::string &config) const;
    LocationBlock CreateLocation(  std::string &LocationTxt) const;

    ServerBlock createServer(std::string &config) const;

    bool validateServer(const ServerBlock &server);

    void createCluster(const std::string &config_file);

};