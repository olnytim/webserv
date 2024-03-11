#include "LocationBlock.hpp"
#include "exceptions.hpp"

LocationBlock::LocationBlock(){
	keywordsMap["return"] = &LocationBlock::setRedirect_map;
	keywordsMap["root"] = &LocationBlock::setRoot;
	keywordsMap["methods"] = &LocationBlock::setMethods;
	keywordsMap["index"] = &LocationBlock::setIndex;
	keywordsMap["autoindex"] = &LocationBlock::setAutoindex;
	keywordsMap["client_body_temp_path"] = &LocationBlock::setClient_body_temp_path;
	keywordsMap["client_max_body_size"] = &LocationBlock::setClient_max_body_size;
	keywordsMap["cgi_pass"] = &LocationBlock::setCgi_pass;

//	keywordsMap["limit_except"] = &LocationBlock::setAllowed_methods;
}

void LocationBlock::reportError() const{

}


void LocationBlock::callFunction(const std::string &key, const std::string &str){
	typedef void (LocationBlock::*MemberFuncType)(std::string);
	MemberFuncType func = keywordsMap[key];
	if (!func || str.size() == 0){
		//Throw exception omaygot
	}
	(this->*func)(str);
}

void LocationBlock::setAutoindex(std::string line){
	if (line == "on"){
		autoindex = true;
	} else if (line == "off"){
		autoindex = false;
	} else{
		//throw error
	}
}
	
void LocationBlock::setRedirect_map(std::string line){
	short status_code;
	std::string status_code_txt;
	std::string link_to_redirect;
	std::stringstream ss(line);

	getline(ss, status_code_txt, ' ');
	getline(ss, link_to_redirect, ' ');
	ss.str(std::string());
	ss << status_code_txt;
	if (!(ss >> status_code) || link_to_redirect.size() == 0){
		//throw error
	}
	redirect_map[status_code] = link_to_redirect;
}

void LocationBlock::setRoot(std::string line){
	root = line;
}

void LocationBlock::setMethods(std::string line){
	std::stringstream ss(line);
	std::string meth;

	while (getline(ss, meth, ' ')){
		methods.push_back(meth);
	}
}

void LocationBlock::setCgi_pass(std::string line){
	cgi_pass = line;
}

void LocationBlock::setIndex(std::string line){
	index = line;
}

void LocationBlock::setRoute_to_be_saved(std::string line){
	(void)line;
}

void LocationBlock::setClient_body_temp_path(std::string line){
	client_body_temp_path = line;
}

void LocationBlock::setClient_max_body_size(std::string line){
	std::istringstream iss(line);
	
	if (!(iss >> client_max_body_size)){
		//throw error
	}
}