#pragma once

#include <sstream>
#include <iostream>

class Request{
private:
	std::string method;
	std::string requestTarget;

public:
	const std::string &getMethod() const;
	const std::string &getRequestTarget() const;
	void setMethod(const std::string &str);
	void setRequestTarget(const std::string &str);
};
