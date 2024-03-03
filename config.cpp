#include "config.hpp"

void configFile::parseError(const parseException &ex){
	throw (ex);
}

void configFile::openConfig(){
	this->config.open("test.conf");
	if (!config.is_open()){
		parseError(configFileException("Could not open the config file"));
	}
}

size_t configFile::skipWhitespace(const std::string &line, size_t pos){
	if (pos >= line.size()){
		//throw an error
	}
	while (line[pos] == ' ' || line[pos] == '	' || line[pos] == '\n'){
		pos++;
		if (pos >= line.size()){
		//throw an error
		}
	}
	return (pos);
}

size_t configFile::findPair(const std::string &line, size_t pos){
	if (pos >= line.size()){
		//throw an error
	}
	while (line[pos] != '}'){
		if (pos >= line.size()){
			//throw an error
		}
		if (line[pos] == '{'){
			pos = findPair(line, pos);
		}
		pos++;
	}
	return (pos);
}

void configFile::divideServers(const std::string &line){
	size_t pos1 = 0;
	size_t pos2 = 0;

	while ((pos1 = line.find("server", pos1)) != std::string::npos){
		pos1 += 6;
		pos1 = skipWhitespace(line, pos1);
		if (line[pos1] == '{'){
			pos2 = findPair(line, pos1++);
		} else {
			//throw an error
		}
		serversTxt.push_back(line.substr(pos1, pos2));
		pos1 = skipWhitespace(line, ++pos2);
	}
}

void configFile::parse(){
	std::string line;

	getline(config, line, '\0');
	divideServers(line);
}