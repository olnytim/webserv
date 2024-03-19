#pragma once

#include "IConfigParse.hpp"
#include "ServerBlock.hpp"
#include <fstream>
#include "IReportError.hpp"
#include "LocationBlock.hpp"

class ConfigFile : public IConfigParse{
public:
	void reportError(const ParseException &ex) const;

	void parse();
	void openConfig();
	void divideIntoServers(const std::string &line);
	void parseServers();
	void removeComments(std::string &line);
	void cutLocations();

	static size_t skipWhitespace(const std::string &line, size_t pos);
	size_t findPair(const std::string &line, size_t pos) const;
private:
	std::ifstream config;
	std::vector<ServerBlock> servers;
	std::vector<std::string> serversTxt;
};
