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

void LocationBlock::reportError(const ParseException &ex) const{
	throw (ex);
}

void LocationBlock::callFunction(const std::string &key, const std::string &str){
	typedef void (LocationBlock::*MemberFuncType)(const std::string&);
	MemberFuncType func = keywordsMap[key];
	if (!func || str.size() == 0){
		reportError(locationParseException("Invalid keyword or content for keyword in Location Block"));
	}
	(this->*func)(str);
}

void LocationBlock::setAutoindex(const std::string &line){
	if (line == "on"){
		autoindex = true;
	} else if (line == "off"){
		autoindex = false;
	} else{
		reportError(locationParseException("Invalid Autoindex value in Location Block"));
	}
}
	
void LocationBlock::setRedirect_map(const std::string &line){
	short status_code;
	std::string status_code_txt;
	std::string link_to_redirect;
	std::stringstream ss(line);

	getline(ss, status_code_txt, ' ');
	getline(ss, link_to_redirect, ' ');
	ss.str(std::string());
	ss << status_code_txt;
	if (!(ss >> status_code) || link_to_redirect.size() == 0){
		reportError(locationParseException("Invalid Return value in Location Block"));
	}
	redirect_map[status_code] = link_to_redirect;
}

void LocationBlock::setRoot(const std::string &line){
	root = line;
}

void LocationBlock::setMethods(const std::string &line){
	std::stringstream ss(line);
	std::string meth;

	while (getline(ss, meth, ' ')){
		methods.push_back(meth);
	}
}

void LocationBlock::setCgi_pass(const std::string &line){
	cgi_pass = line;
}

void LocationBlock::setIndex(const std::string &line){
	index = line;
}

void LocationBlock::setRoute_to_be_saved(const std::string &line){
	(void)line;
}

void LocationBlock::setClient_body_temp_path(const std::string &line){
	client_body_temp_path = line;
}

void LocationBlock::setClient_max_body_size(const std::string &line){
	std::istringstream iss(line);
	
	if (!(iss >> client_max_body_size)){
		reportError(locationParseException("Invalid Client_max_body_size value in Location Block"));
	}
}