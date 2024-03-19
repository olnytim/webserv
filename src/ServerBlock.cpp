#include "../includes/ServerBlock.hpp"
#include "../includes/config.hpp"

ServerBlock::ServerBlock(){
	keywords["server_name"] = &ServerBlock::setServerName;
	keywords["port"] = &ServerBlock::setPort;
	keywords["client_max_body_size"] = &ServerBlock::setClientMaxBodySize;
	keywords["listen"] = &ServerBlock::setListen;
	keywords["error_page"] = &ServerBlock::addErrorPage;

}

void ServerBlock::reportError(const ParseException &ex) const{
	throw (ex);
}

const std::vector<std::string> &ServerBlock::getLocationsTxt() const{
	return (locationsTxt);
}

void ServerBlock::callFunction(const std::string &key, std::string str){
	typedef void (ServerBlock::*MemberFuncType)(const std::string&);
	MemberFuncType func = keywords[key];
	if (!func || str.size() == 0){
		reportError(locationParseException("Invalid keyword or content for keyword in Server Block"));
	}
	(this->*func)(const_cast<const std::string&>(str));
}

void ServerBlock::setServerName(const std::string &line){
	std::stringstream ss(line);
	std::string tmp;
	while (getline(ss, tmp, ' ')){
		server_names.push_back(tmp);
	}
}

void ServerBlock::addErrorPage(const std::string &line){
	std::string error_num = line.substr(0, line.find(" "));
	std::string error_page = line.substr(line.find(" ") + 1);
	std::istringstream iss(error_num);
	unsigned short key;
	if (!(iss >> key)){
		reportError(serverParseException("Invalid Error page value in ServerBlock"));
	}
	error_pages[key] = error_page;
}

void ServerBlock::setClientMaxBodySize(const std::string &line){
	std::istringstream iss(line);
	
	if (!(iss >> client_max_body_size)){
		reportError(serverParseException("Invalid Client max body size in ServerBlock"));
	}
}

void ServerBlock::setListen(const std::string &line){
	listen = line;
}

void ServerBlock::setPort(const std::string &line){
	std::istringstream iss(line);
	if (!(iss >> port)){
		reportError(serverParseException("Invalid Port in ServerBlock"));
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

void ServerBlock::addLocation(const LocationBlock &loc){
	locations.push_back(loc);
}

const std::vector<std::string> &ServerBlock::getServerNames() const{
    return (server_names);
}

const std::vector<LocationBlock> &ServerBlock::getLocations() const{
    return (locations);
}

const std::map<unsigned short, std::string> ServerBlock::getErrorPage() const{
    return (error_pages);
}

std::string ServerBlock::getListen() const{
    return (listen);
}

unsigned short ServerBlock::getPort() const{
    return (port);
}

unsigned int ServerBlock::getClientMaxBodySize() const{
    return (client_max_body_size);
}