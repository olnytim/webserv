#pragma once

#include <fstream>
#include <iostream>
#include <vector>

class parseException : public std::exception {
public:
	parseException(const std::string& message) : _message(message) {}
	virtual const char* what() const throw() {
		return _message.c_str();
	}
	virtual ~parseException() throw() {}
private:
	const std::string _message;
};

class configFileException : public parseException {
public:
	configFileException(const std::string &message) : parseException(message){}
};

class configException : public parseException {
public:
	configException(const std::string &message) : parseException(message){}
};

class IconfigParse{
public:
	virtual	void parse() = 0;
	virtual void parseError(const parseException &ex) const = 0;
	virtual void openConfig() = 0;
	virtual void divideIntoServers(const std::string &line) = 0;
	virtual void parseServers() = 0;
	virtual void removeComments(std::string &line) = 0;

	virtual size_t skipWhitespace(const std::string &line, size_t pos) const = 0;
	virtual size_t findPair(const std::string &line, size_t pos) const = 0;
};

class locationBlock{
private:

};

class serverBlock{
private:
	std::string server_name;
	std::vector<locationBlock> locations;
	
public:
	void setServer_name();
	void addLocation();
};

class configFile : public IconfigParse {
public:
	void parse();
	void parseError(const parseException &ex) const;
	void openConfig();
	void divideIntoServers(const std::string &line);
	void parseServers();
	void removeComments(std::string &line);
	
	size_t skipWhitespace(const std::string &line, size_t pos) const;
	size_t findPair(const std::string &line, size_t pos) const;
private:
	std::ifstream config;
	std::vector<serverBlock> servers;
	std::vector<std::string> serversTxt;
};
