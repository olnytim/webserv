#pragma once

#include <fstream>
#include <iostream>
#include <vector>

// class parseException : public std::exception {
// public:
// 	parseException(const std::string &message) : _message(message) {}
// 	const char* what() const throw(){
// 		return (_message.c_str());
// 	}
// private:
// 	const std::string _message;
// };

// class configFileException : public parseException{
// public:
// 	configFileException(const std::string &message) : parseException(message){}
// };

class parseException : std::exception {
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

class configParse{
public:
	virtual void parseError(const parseException &ex) = 0;
	virtual void openConfig() = 0;
	virtual void divideServers(const std::string &line) = 0;
	virtual size_t skipWhitespace(const std::string &line, size_t pos) = 0;
	virtual size_t findPair(const std::string &line, size_t pos) = 0;
	virtual	void parse() = 0;
};

class serverBlock{

};

class configFile : public configParse {
public:
	void parseError(const parseException &ex);
	void openConfig();
	void divideServers(const std::string &line);
	size_t skipWhitespace(const std::string &line, size_t pos);
	size_t findPair(const std::string &line, size_t pos);
	void parse();
private:
	std::ifstream config;
	std::vector<serverBlock> servers;
	std::vector<std::string> serversTxt;
};