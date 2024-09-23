#pragma once

#include "../Headers.hpp"
#include "exceptions.hpp"
#include "ServerBlock.hpp"
#include "parsingUtils.hpp"
#include "parsingValidator.hpp"

class Config {
private:
    std::vector<ServerBlock>    servers;
    std::vector<std::string>    server_config;
//    size_t                      amount_of_servers;

    std::string                 conf_file;

public:
    Config();
    ~Config();

    static int getTypePath(const std::string &path);
    static std::string getContent(const std::string &path);
    const std::string &getFile() const;
    const std::vector<ServerBlock> &getServers() const;

    static bool isFileExistAndReadable(const std::string &path, const std::string &index);

    std::vector<std::string> SplitAndCutLocations(std::string &config) const;

    std::map<std::string, std::string> MapExtPath(const std::vector<std::string> &cgi_path,
                                                  const std::vector<std::string> &cgi_ext) const;

    LocationBlock CreateLocation(std::string &locationTxt) const;
    std::vector<LocationBlock> ParseConfigLocations(std::string &config) const;

    static void parseConfig(std::string &content);
    void splitServers(std::string &content);
    ServerBlock createServer(std::string &serverTxt) const;
    void createCluster(const std::string &config_file);
};