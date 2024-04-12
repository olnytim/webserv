#pragma once

#include "Request.hpp"

class RequestParsing{
private:
	Request &request;
	RequestParsing();
public:
	RequestParsing(Request &request);
	void parseRequestLine(const std::string &reqLine);
	void parseBody(const std::string &body);
	void parseHeaders(const std::string &headers);

	void parse(const std::string &request);
	void method(std::stringstream &req);
	void requestTarget(std::stringstream &req);
	void httpVersion(std::stringstream &req);
};
