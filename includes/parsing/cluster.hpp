#pragma once

#include "../Headers.hpp"
#include "exceptions.hpp"
#include "serve.hpp"

class Config {
private:
    std::vector<ServerBlock>    servers;
    std::vector<std::string>    server_config;
    size_t                      amount_of_servers;

    std::string                 conf_file;

public:
    Config();
    ~Config();

    void reportError(const ParseException &ex) const;

    static int getTypePath(const std::string &path);
    static std::string getContent(const std::string &path);
    static bool isFileExistAndReadable(const std::string &path, const std::string &index);

    const std::string &getFile() const;
    const std::vector<ServerBlock> &getServers() const;

    static void parseConfig(std::string &content);
    void splitServers(const std::string &content);
    static std::vector<std::string> splitParams(const std::string &content, const std::string &delim);
    void createServer(std::string &config, ServerBlock &server) const;
    void createCluster(const std::string &config_file);

    void print() const;
};