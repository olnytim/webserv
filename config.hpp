#pragma once

#include "IConfigParse.hpp"
#include "ServerBlock.hpp"
#include "exceptions.hpp"
#include <fstream>
#include <sstream>

/// configFile
class ConfigFile : public IConfigParse {
public:

	void parse();
	void reportError(const ParseException &ex) const;
	void openConfig();
	void divideIntoServers(const std::string &line);
	void parseServers();
	void removeComments(std::string &line);
	void cutLocations();

	size_t skipWhitespace(const std::string &line, size_t pos) const;
	size_t findPair(const std::string &line, size_t pos) const;
private:
	std::ifstream config;
	std::vector<ServerBlock> servers;
	std::vector<std::string> serversTxt;
};
