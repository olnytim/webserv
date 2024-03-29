#pragma once

#include <sstream>
#include <iostream>

class RequestParsing{
	virtual void parse(const std::string &request) = 0;
	virtual void parseRequestLine(const std::string &reqLine) = 0;
};

class Request : public RequestParsing{
private:
	std::string method;
public:
	const std::string &getRequestLine() const;

	void setRequestLine(const std::string &str);
	void parse(const std::string &request);
	void parseRequestLine(const std::string &reqLine);
};