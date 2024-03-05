#include "config.hpp"

void ConfigFile::reportError(const ParseException &ex) const{
	throw (ex);
}

void ConfigFile::openConfig(){
	this->config.open("test.conf");
	if (!config.is_open()){
		reportError(configFileException("Could not open the config file"));
	}
}

size_t ConfigFile::skipWhitespace(const std::string &line, size_t pos) const{
	while (pos < line.size() && (line[pos] == ' ' || line[pos] == '	' || line[pos] == '\n'))
		pos++;
	return (pos);
}

size_t ConfigFile::findPair(const std::string &line, size_t pos) const{
	if (pos >= line.size())
		reportError(configFileException("Invalid configuration"));
	while (line[pos] != '}'){
		if (pos >= line.size()){
			reportError(configFileException("Invalid configuration"));
		}
		if (line[pos] == '{'){
			pos = findPair(line, pos + 1);
		}
		pos++;
	}
	return (pos);
}

void ConfigFile::divideIntoServers(const std::string &line) {
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
			reportError(configFileException("Invalid configuration"));
	}
	
	for (size_t i = 0; i < serversTxt.size(); i++){
		std::cout << "[" << serversTxt[i] << "]" << std::endl << std::endl;
	}
}

void ConfigFile::removeComments(std::string &line) {
	size_t pos;
	std::string line1;
	std::string line2;

	while ((pos = line.find('#')) != std::string::npos){
		line1 = line.substr(0, pos - 1);
		line2 = line.substr(line.find('\n', pos));
		line = line1 + line2;
	}
}
/*
void ServerBlock::setServerName(std::string &line){
	
}
void ServerBlock::addLocation(std::string &line){

}
void ServerBlock::addErrorPage(std::string &line){

}
void ServerBlock::setClientMaxBodySize(std::string &line){

}
void ServerBlock::setAutoindex(std::string &line){

}
void ServerBlock::setListen(std::string &line){

}
void ServerBlock::setPort(std::string &line){

}
*/
void ServerBlock::addLocationTxt(std::string str){
	locationsTxt.push_back(str);
}

void ConfigFile::cutLocations(){
	size_t pos1 = 0;
	size_t pos2 = 0;

	for(size_t i = 0; i < serversTxt[i].size(); i++){
		ServerBlock server;
		while ((pos1 = serversTxt[i].find("location", pos1)) != std::string::npos){
			pos1 += 8;
			pos1 = skipWhitespace(serversTxt[i], pos1);
			if (pos1 < serversTxt[i].size() && serversTxt[i][pos1] == '/')
				pos1 = serversTxt[i].find(' ', pos1);
			pos1 = skipWhitespace(serversTxt[i], pos1);
			if (pos1 < serversTxt[i].size() && serversTxt[i][pos1] == '{'){
				pos2 = findPair(serversTxt[i], ++pos1);
				servers[i].addLocationTxt(serversTxt[i].substr(pos1, pos2 - pos1));
				pos1 = skipWhitespace(serversTxt[i], pos2 + 1);
			} else
				reportError(configFileException("Invalid configuration"));
		}
		servers.push_back(server);
	}
}

void ConfigFile::parseServers(){
	cutLocations();
/*	std::string line;
	std::string key;
	std::map<std::string, void(*)(std::string)> keywords;
	if (serversTxt.size() < 1)
		reportError(configException("No server configuration in the config file"));

	for (size_t i = 0; i < serversTxt.size(); i++){
		std::stringstream ss(serversTxt[i]);
		while (getline(ss, line, ';')){
			size_t pos = skipWhitespace(line, 0);
			key = line.substr(pos , line.find(' ', pos) - pos);
			keywords[key](line.substr(line.find(' ', pos)));
		}
	}*/
}



void ConfigFile::parse(){
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
