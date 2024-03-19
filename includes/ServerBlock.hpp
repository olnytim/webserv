#pragma once

#include "LocationBlock.hpp"

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
public:
	ServerBlock();

	void callFunction(const std::string &key, std::string str);

	void setServerName(const std::string &line);
	void addErrorPage(const std::string &line);
	void setClientMaxBodySize(const std::string &line);
	void setListen(const std::string &line);
	void setPort(const std::string &line);
	void addLocationTxt(std::string str);
	void parseLocations();
	void addLocation(const LocationBlock &loc);
	void reportError(const ParseException &ex) const;

	const std::vector<std::string> &getServerNames() const;
	const std::vector<LocationBlock> &getLocations() const;
	const std::map<short, std::string> getErrorPage() const;
	const std::vector<std::string> &getLocationsTxt() const;
};
