#pragma once

//#include <iostream>
// #include "../Headers.hpp"

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

class configParseException : public ParseException {
public:
	configParseException(const std::string &message) : ParseException(message){}
};

class locationParseException : public ParseException {
public:
	locationParseException(const std::string &message) : ParseException(message){}
};

class serverParseException : public ParseException {
public:
	serverParseException(const std::string &message) : ParseException(message){}
};
