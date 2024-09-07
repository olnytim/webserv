#include "../../includes/parsing/LocationBlockKeymap.hpp"
#include "../../includes/parsing/exceptions.hpp"
#include "../../includes/parsing/loca.hpp"

LocationBlockKeymap::LocationBlockKeymap(){
	keymap["root"] = &LocationBlock::setRoot;
    keymap["index"] = &LocationBlock::setIndex;
    keymap["return"] = &LocationBlock::setReturn;
    keymap["alias"] = &LocationBlock::setAlias;
    keymap["cgi_path"] = &LocationBlock::setCgiPath;
    keymap["cgi_ext"] = &LocationBlock::setCgiExt;
    keymap["methods"] = &LocationBlock::setMethods;
    keymap["autoindex"] = &LocationBlock::setAutoindex;
    keymap["client_max_body_size"] = &LocationBlock::setClientMaxBodySize;
}

void LocationBlockKeymap::callFunction(std::string key, const std::string &value, LocationBlock &instance) const
{
		typedef void (LocationBlock::*MemberFuncType)(const std::string&);
		MemberFuncType func = keymap.find(key)->second;
		if (key.size() == 0 || value.size() == 0 || !func){
			errorHandler::reportError(locationParseException("Invalid keyword or content for keyword in Location Block"));
		}
		(instance.*func)(value);
}

//void LocationBlock::callFunction(const std::string &key, const std::string &str){
//	typedef void (LocationBlock::*MemberFuncType)(const std::string&);
//	MemberFuncType func = keywordsMap[key];
//	if (!func || str.size() == 0){
//		reportError(locationParseException("Invalid keyword or content for keyword in Location Block"));
//	}
//	(this->*func)(str);
//}
//
//void LocationBlock::setAutoindex(const std::string &line){
//	if (line == "on"){
//		autoindex = true;
//	} else if (line == "off"){
//		autoindex = false;
//	} else{
//		reportError(locationParseException("Invalid Autoindex value in Location Block"));
//	}
//}
//
//void LocationBlock::setRedirect_map(const std::string &line){
//	short status_code;
//	std::string status_code_txt;
//	std::string link_to_redirect;
//	std::stringstream ss(line);
//
//	getline(ss, status_code_txt, ' ');
//	getline(ss, link_to_redirect, ' ');
//	ss.str(std::string());
//	ss << status_code_txt;
//	if (!(ss >> status_code) || link_to_redirect.size() == 0){
//		reportError(locationParseException("Invalid Return value in Location Block"));
//	}
//	redirect_map[status_code] = link_to_redirect;
//}
//
//void LocationBlock::setRoot(const std::string &line){
//	root = line;
//}
//
//void LocationBlock::setMethods(const std::string &line){
//	std::stringstream ss(line);
//	std::string meth;
//
//	while (getline(ss, meth, ' ')){
//		methods.push_back(meth);
//	}
//}
//
//void LocationBlock::setCgi_pass(const std::string &line){
//	cgi_pass = line;
//}
//
//void LocationBlock::setIndex(const std::string &line){
//	index = line;
//}
//
//void LocationBlock::setRoute_to_be_saved(const std::string &line){
//	(void)line;
//}
//
//void LocationBlock::setClient_body_temp_path(const std::string &line){
//	client_body_temp_path = line;
//}
//
//void LocationBlock::setClient_max_body_size(const std::string &line){
//	std::istringstream iss(line);
//
//	if (!(iss >> client_max_body_size)){
//		reportError(locationParseException("Invalid Client_max_body_size value in Location Block"));
//	}
//}
//
//const std::string &LocationBlock::getRoot() const{
//    return (root);
//}
//
//const std::string &LocationBlock::getIndex() const{
//    return (index);
//}
//
//const std::string &LocationBlock::getRoute_to_be_saved() const{
//    return (route_to_be_saved);
//}
//
//const std::string &LocationBlock::getClient_body_temp_path() const{
//    return (client_body_temp_path);
//}
//
//const std::string &LocationBlock::getCgi_pass() const{
//    return (cgi_pass);
//}
//
//const std::vector<std::string> &LocationBlock::getMethods() const{
//    return (methods);
//}
//
//const std::map<short, std::string> &LocationBlock::getRedirect_map() const{
//    return (redirect_map);
//}
//
//unsigned int LocationBlock::getClient_max_body_size() const{
//    return (client_max_body_size);
//}
//
//bool LocationBlock::getAutoindex() const{
//    return (autoindex);
//}