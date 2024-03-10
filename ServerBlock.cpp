#include "ServerBlock.hpp"
#include "config.hpp"

ServerBlock::ServerBlock(){
	keywords["server_name"] = &ServerBlock::setServerName;
	keywords["port"] = &ServerBlock::setPort;
	keywords["client_max_body_size"] = &ServerBlock::setClientMaxBodySize;
	keywords["listen"] = &ServerBlock::setListen;
}

const std::vector<std::string> &ServerBlock::getLocationsTxt() const{
	return (locationsTxt);
}

void ServerBlock::callFunction(const std::string &key, const std::string &str){
	typedef void (ServerBlock::*MemberFuncType)(std::string);
	MemberFuncType func = keywords[key];
	if (!func || str.size() == 0){
		//Throw exception omaygot
	}
	(this->*func)(str);
}

void ServerBlock::setServerName(std::string line){
	std::stringstream ss(line);
	std::string tmp;
	while (getline(ss, tmp, ' ')){
		server_names.push_back(tmp);
	}
}

void ServerBlock::addLocation(){
	locationBlock lb;
	locations.push_back(lb);
}

void ServerBlock::addErrorPage(std::string line){
	std::string error_num = line.substr(0, line.find(" "));
	std::string error_page = line.substr(line.find(" ") + 1);
	std::istringstream iss(error_num);
	unsigned short key;
	if (!(iss >> key)){
		//throw error
	}
	error_pages[key] = error_page;
}

void ServerBlock::setClientMaxBodySize(std::string line){
	std::istringstream iss(line);
	
	if (!(iss >> client_max_body_size)){
		//throw error
	}
}

void ServerBlock::setListen(std::string line){
	listen = line;
}

void ServerBlock::setPort(std::string line){
	std::istringstream iss(line);
	if (!(iss >> port)){
		//throw error
	}
}
void ServerBlock::addLocationTxt(std::string str){
	locationsTxt.push_back(str);
}

void ServerBlock::parseLocations(){
	std::string line;
	std::string key;

	for (size_t i = 0; i < locationsTxt.size(); i++){
		std::stringstream ss(locationsTxt[i]);
		while (getline(ss, line, ';')){
			size_t pos = ConfigFile::skipWhitespace(line, 0);
			if (pos == line.size())
				break ;
			key = line.substr(pos , line.find(' ', pos) - pos);
			locations[i].callFunction(key, line.substr(line.find(' ', pos) + 1));
		}
	}
}