#include "ServerBlock.hpp"

ServerBlock::ServerBlock(){
	keywords["server_name"] = &ServerBlock::setServerName;
	keywords["port"] = &ServerBlock::setPort;
	keywords["client_max_body_size"] = &ServerBlock::setClientMaxBodySize;
	keywords["autoindex"] = &ServerBlock::setAutoindex;
	keywords["listen"] = &ServerBlock::setListen;
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
	server_names.push_back(line);
}

void ServerBlock::addLocation(std::string line){
(void)line;
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

void ServerBlock::setAutoindex(std::string line){
	if (line == "on")
		autoindex = true;
	else if (line == "off")
		autoindex = false;
	else{
		//throw error
		;
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
