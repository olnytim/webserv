#pragma once

#include "exceptions.hpp"

class IConfigParse{
public:
	virtual	void parse() = 0;
	virtual void openConfig() = 0;
	virtual void divideIntoServers(const std::string &line) = 0;
	virtual void parseServers() = 0;
	virtual void removeComments(std::string &line) = 0;
	virtual void cutLocations() = 0;
	virtual size_t findPair(const std::string &line, size_t pos) const = 0;
};