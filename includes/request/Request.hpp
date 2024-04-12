#pragma once

#include <sstream>
#include <iostream>
#include <map>

class Request{
private:
	std::string method;
	std::string requestTarget;
	std::string version;
	std::map<std::string, std::string> headersMap;
public:
	const std::string &getMethod() const;
	const std::string &getRequestTarget() const;
	const std::string &getVersion() const;
	const std::string &getHeadersMap() const;

	void setMethod(const std::string &str);
	void setRequestTarget(const std::string &str);
	void setVersion(const std::string &version);
	void setHeadersMap(const std::map<std::string, std::string> &headersMap);
};
