#pragma once

#include <sstream>
#include <iostream>

class Request{
private:
	std::string method;
public:

	const std::string &getRequestLine() const;

	void setRequestLine(const std::string &str);
};

class RequestParsing{
private:
	Request &req;
	RequestParsing();
public:
	RequestParsing(Request &request);
	void parseRequestLine(const std::string &reqLine, Request &ref);
	void requestTarget(std::stringstream &req);
	void method(std::stringstream &req);
	void parse(const std::string &request);
};
