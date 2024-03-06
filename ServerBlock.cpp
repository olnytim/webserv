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
	(this->*func)(str);
}

void ServerBlock::setServerName(std::string line){
	(void)line;
	std::cout << "servername called" << std::endl;
}
void ServerBlock::addLocation(std::string line){
	(void)line;
	std::cout << "addlocation called" << std::endl;
}
void ServerBlock::addErrorPage(std::string line){
	(void)line;
	std::cout << "adderrorpage called" << std::endl;

}
void ServerBlock::setClientMaxBodySize(std::string line){
	(void)line;
	std::cout << "setclientmaxbodysize called" << std::endl;

}
void ServerBlock::setAutoindex(std::string line){
	(void)line;
	std::cout << "setautoindex called" << std::endl;

}
void ServerBlock::setListen(std::string line){
	(void)line;
	std::cout << "setlisten called" << std::endl;
}

void ServerBlock::setPort(std::string line){
	(void)line;
	std::cout << "setPort called" << std::endl;

}

void ServerBlock::addLocationTxt(std::string str){
	locationsTxt.push_back(str);
}
