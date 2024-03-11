#pragma once

#include "LocationBlock.hpp"

class Block : public IReportError{ //abstract class for location and server
	void reportError() const;
};

void Block::reportError() const{
	throw(ex);
}

class ServerBlock : public Block{
private:
	std::string listen;
	std::vector<std::string> server_names;
	std::map<unsigned short, std::string> error_pages;
	std::vector<LocationBlock> locations;
	std::vector<std::string> locationsTxt;
	std::map<std::string, void(ServerBlock::*)(std::string)> keywords;
	unsigned int client_max_body_size;
	unsigned short port;
public:
	ServerBlock();
	

	void callFunction(const std::string &key, const std::string &str);
	void setServerName(std::string line);
	void addLocation();
	void addErrorPage(std::string line);
	void setClientMaxBodySize(std::string line);
	void setListen(std::string line);
	void setPort(std::string line);
	void addLocationTxt(std::string str);
	void parseLocations();

	std::vector<std::string> &getServerNames() const;
	std::vector<LocationBlock> &getLocations() const;
	std::map<short, std::string> getErrorPage() const;
	const std::vector<std::string> &getLocationsTxt() const;
};
