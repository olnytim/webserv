#pragma once

#include "../Utils.hpp"

class ServerBlock {
private:
	typedef void(ServerBlock::*func)(const std::string&);
	std::map<const std::string, func> keywords;
	std::map<unsigned short, std::string> error_pages;
	
	std::vector<std::string> server_names;
	std::vector<LocationBlock> locations;
	std::vector<std::string> locationsTxt;
	std::string listen;
	
	unsigned int client_max_body_size;
	unsigned short port;

    in_addr_t host;
    std::string server_name;
    std::string root;
    std::string index;
    bool autoindex;
    struct sockaddr_in server_address;
    int listen_fd;

public:
	ServerBlock();

	void callFunction(const std::string &key, std::string str);
    void addErrorPage(const std::string &line);
    void addLocationTxt(std::string str);
    void addLocation(const LocationBlock &loc);
    void parseLocations();
    void reportError(const ParseException &ex) const;
    void checkToken(std::string &param) const;
    bool checkLocations() const;

    void setServerNames(const std::string &line);
    void setServerName(const std::string &line);
    void setClientMaxBodySize(const std::string &line);
    void setListen(const std::string &line);
    void setPort(const std::string &line);
    void setHost(std::string &line);
    void setRoot(const std::string &line);
    void setIndex(const std::string &line);
    void setAutoindex(const std::string &line);
    void setErrorPages(const std::vector<std::string> &line);
    void setFd(int fd);

	const std::vector<std::string> &getServerNames() const;
    const std::vector<LocationBlock> &getLocations() const;
    const std::map<unsigned short, std::string> getErrorPage() const;
    const std::vector<std::string> &getLocationsTxt() const;
    std::string getListen() const;
    unsigned short getPort() const;
    unsigned int getClientMaxBodySize() const;
    const std::string &getServerName() const;
    in_addr_t getHost() const;
    const std::string &getRoot() const;
    const std::string &getIndex() const;
    bool getAutoindex() const;
    int getFd() const;

    void setupServer();
    bool isValidHost(std::string host) const;
    bool isValidErrorPages();
    int isValidLocation(LocationBlock &location) const;
};
