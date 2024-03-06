#pragma once

#include <iostream>

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