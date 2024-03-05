#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>

class ParseException : public std::exception {
public:
	ParseException(const std::string& message) : _message(message) {}
	virtual const char* what() const throw() {
		return _message.c_str();
	}
	virtual ~ParseException() throw() {}
private:
	const std::string _message;
};

class configFileException : public ParseException {
public:
	configFileException(const std::string &message) : ParseException(message){}
};

class configException : public ParseException {
public:
	configException(const std::string &message) : ParseException(message){}
};

class IConfigParse{
public:
	virtual	void parse() = 0;
	virtual void reportError(const ParseException &ex) const = 0;
	virtual void openConfig() = 0;
	virtual void divideIntoServers(const std::string &line) = 0;
	virtual void parseServers() = 0;
	virtual void removeComments(std::string &line) = 0;
	virtual void cutLocations() = 0;
	virtual size_t skipWhitespace(const std::string &line, size_t pos) const = 0;
	virtual size_t findPair(const std::string &line, size_t pos) const = 0;
};

class LocationBlock{
private:

};

//serverblock
class ServerBlock{
private:
	std::string listen;
	std::vector<std::string> server_names;
	std::map<unsigned short, std::string> error_page;
	unsigned int client_max_body_size;
	bool autoindex;
	short port;
	std::vector<LocationBlock> locations;
	std::vector<std::string> locationsTxt;
public:
	void setServerName();
	void addLocation();
	void addErrorPage();
	void setClientMaxBodySize();
	void setAutoindex();
	void setListen();
	void setPort();
	void addLocationTxt(std::string str);
	std::vector<std::string> &getServerNames() const;
	std::vector<LocationBlock> &getLocations() const;
	std::map<short, std::string> getErrorPage() const;
};

class ConfigFile : public IConfigParse {
public:

	void parse();
	void reportError(const ParseException &ex) const;
	void openConfig();
	void divideIntoServers(const std::string &line);
	void parseServers();
	void removeComments(std::string &line);
	void cutLocations();

	size_t skipWhitespace(const std::string &line, size_t pos) const;
	size_t findPair(const std::string &line, size_t pos) const;
private:
	std::ifstream config;
	std::vector<ServerBlock> servers;
	std::vector<std::string> serversTxt;
};
