#pragma once

#include <vector>
#include <map>
#include <sstream>
#include <iostream>

class LocationBlock{
private:

};

class ServerBlock{
private:
	std::string listen;
	std::vector<std::string> server_names;
	std::map<unsigned short, std::string> error_pages;
	unsigned int client_max_body_size;
	bool autoindex;
	unsigned short port;
	std::vector<LocationBlock> locations;
	std::vector<std::string> locationsTxt;
	std::map<std::string, void(ServerBlock::*)(std::string)> keywords;
public:
	ServerBlock();

	void callFunction(const std::string &key, const std::string &str);
	void setServerName(std::string line);
	void addLocation(std::string line);
	void addErrorPage(std::string line);
	void setClientMaxBodySize(std::string line);
	void setAutoindex(std::string line);
	void setListen(std::string line);
	void setPort(std::string line);
	void addLocationTxt(std::string str);
	const std::map<std::string, void(ServerBlock::*)(std::string)> &getKeywords() const;

	std::vector<std::string> &getServerNames() const;
	std::vector<LocationBlock> &getLocations() const;
	std::map<short, std::string> getErrorPage() const;
};
