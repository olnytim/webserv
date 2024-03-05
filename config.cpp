#include "config.hpp"
#include <sstream>

void configFile::parseError(const parseException &ex) const{
	throw (ex);
}

void configFile::openConfig(){
	this->config.open("test.conf");
	if (!config.is_open()){
		parseError(configFileException("Could not open the config file"));
	}
}

size_t configFile::skipWhitespace(const std::string &line, size_t pos) const{
	while (pos < line.size() && (line[pos] == ' ' || line[pos] == '	' || line[pos] == '\n'))
		pos++;
	return (pos);
}

size_t configFile::findPair(const std::string &line, size_t pos) const{
	if (pos >= line.size())
		parseError(configFileException("Invalid configuration"));
	while (line[pos] != '}'){
		if (pos >= line.size()){
			parseError(configFileException("Invalid configuration"));
		}
		if (line[pos] == '{'){
			pos = findPair(line, pos + 1);
		}
		pos++;
	}
	return (pos);
}

void configFile::divideIntoServers(const std::string &line) {
	size_t pos1 = 0;
	size_t pos2 = 0;

	while ((pos1 = line.find("server", pos1)) != std::string::npos){
		pos1 += 6;
		pos1 = skipWhitespace(line, pos1);
		if (pos1 < line.size() && line[pos1] == '{'){
			pos2 = findPair(line, ++pos1);
			serversTxt.push_back(line.substr(pos1, pos2 - pos1));
			pos1 = skipWhitespace(line, pos2 + 1);
		} else
			parseError(configFileException("Invalid configuration"));
	}
	
	for (size_t i = 0; i < serversTxt.size(); i++){
		std::cout << "[" << serversTxt[i] << "]" << std::endl << std::endl;
	}
}

void configFile::removeComments(std::string &line) {
	size_t pos;
	std::string line1;
	std::string line2;

	while ((pos = line.find('#')) != std::string::npos){
		line1 = line.substr(0, pos - 1);
		line2 = line.substr(line.find('\n', pos));
		line = line1 + line2;
	}
	std::cout << line << std::endl;
}

void configFile::parseServers(){
	if (serversTxt.size() < 1)
		parseError(configException("No server configuration in the config file"));
	for (size_t i = 0; i < serversTxt.size(); i++){
		
	}
}

void configFile::parse(){
	std::string line;

	getline(config, line, '\0');
	try{
		removeComments(line);
	}	catch (const std::out_of_range &e){
		std::cout << e.what();
	}
	divideIntoServers(line);
	parseServers();
}