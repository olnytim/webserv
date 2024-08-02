#include "../../includes/parsing/LocationBlock.hpp"
//#include "../../includes/parsing/exceptions.hpp"

LocationBlock::LocationBlock(){
	keywordsMap["return"] = &LocationBlock::setRedirect_map;
	keywordsMap["root"] = &LocationBlock::setRoot;
	keywordsMap["index"] = &LocationBlock::setIndex;
    keywordsMap["autoindex"] = &LocationBlock::setAutoindex;
    keywordsMap["client_body_temp_path"] = &LocationBlock::setClient_body_temp_path;
    keywordsMap["client_max_body_size"] = &LocationBlock::setClient_max_body_size;

//	keywordsMap["cgi_path"] = reinterpret_cast<void (LocationBlock::*)(
//            const std::string &)>(&LocationBlock::setCgi_path);
//	keywordsMap["methods"] = &LocationBlock::setMethods;
//	keywordsMap["limit_except"] = &LocationBlock::setAllowed_methods;
    path = "";
    root = "";
    index = "";
    return_value = "";
    route_to_be_saved = "";
    client_body_temp_path = "";
    client_max_body_size = MAX_CONTENT_LENGTH;
    autoindex = false;
    methods.reserve(5);
    methods.push_back("GET");
    methods.push_back("null");
    methods.push_back("null");
    methods.push_back("null");
    methods.push_back("null");
}

void LocationBlock::reportError(const ParseException &ex) {
	throw (ex);
}

void LocationBlock::callFunction(const std::string &key, const std::string &str){
	typedef void (LocationBlock::*MemberFuncType)(const std::string&);
	MemberFuncType func = keywordsMap[key];
	if (!func || str.empty()){
		reportError(locationParseException("Invalid keyword or content for keyword in Location Block"));
	}
	(this->*func)(str);
}

void LocationBlock::setAutoindex(const std::string &line){
	if (line == "on") {
		autoindex = true;
	} else if (line == "off") {
		autoindex = false;
	} else {
		reportError(locationParseException("Invalid Autoindex value in Location Block"));
	}
}
	
void LocationBlock::setRedirect_map(const std::string &line) {
	short status_code;
	std::string status_code_txt;
	std::string link_to_redirect;
	std::stringstream ss(line);

	getline(ss, status_code_txt, ' ');
	getline(ss, link_to_redirect, ' ');
	ss.str(std::string());
	ss << status_code_txt;
	if (!(ss >> status_code) || link_to_redirect.empty()){
		reportError(locationParseException("Invalid Return value in Location Block"));
	}
	redirect_map[status_code] = link_to_redirect;
}

void LocationBlock::setRoot(const std::string &line) {
	root = line;
}

int getMethodCode(const std::string& method) {
    if (method == "GET") return 1;
    if (method == "POST") return 2;
    if (method == "DELETE") return 3;
    if (method == "PUT") return 4;
    if (method == "HEAD") return 5;
    return 0;
}

void LocationBlock::setMethods(const std::vector<std::string> &line) {
	methods[0] = "null";
    methods[1] = "null";
    methods[2] = "null";
    methods[3] = "null";
    methods[4] = "null";

    for (size_t i = 0; i < line.size(); i++){
        switch (getMethodCode(line[i])) {
            case 1:
                methods[0] = "GET";
                break;
            case 2:
                methods[1] = "POST";
                break;
            case 3:
                methods[2] = "DELETE";
                break;
            case 4:
                methods[3] = "PUT";
                break;
            case 5:
                methods[4] = "HEAD";
                break;
            default:
                reportError(locationParseException("Invalid Method value in Location Block"));
        }
    }
}

void LocationBlock::setCgi_path(const std::vector<std::string> &line){
	cgi_path = line;
}

void LocationBlock::setCgi_extension(const std::vector<std::string> &line){
    cgi_extension = line;
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

void LocationBlock::setReturn_value(const std::string &line){
    return_value = line;
}

void LocationBlock::setPath(const std::string &line){
    path = line;
}

void LocationBlock::setAlias(const std::string &line){
    alias = line;
}

const std::string &LocationBlock::getRoot() const{
    return (root);
}

const std::string &LocationBlock::getIndex() const{
    return (index);
}

const std::string &LocationBlock::getRoute_to_be_saved() const{
    return (route_to_be_saved);
}

const std::string &LocationBlock::getClient_body_temp_path() const{
    return (client_body_temp_path);
}

const std::vector<std::string> &LocationBlock::getCgi_path() const{
    return (cgi_path);
}

const std::vector<std::string> &LocationBlock::getMethods() const{
    return (methods);
}

const std::map<short, std::string> &LocationBlock::getRedirect_map() const{
    return (redirect_map);
}

unsigned int LocationBlock::getClient_max_body_size() const{
    return (client_max_body_size);
}

bool LocationBlock::getAutoindex() const{
    return (autoindex);
}

const std::vector<std::string> &LocationBlock::getCgi_extension() const{
    return (cgi_extension);
}

const std::string &LocationBlock::getReturn_value() const{
    return (return_value);
}

const std::string &LocationBlock::getPath() const{
    return (path);
}

const std::map<std::string, std::string> &LocationBlock::getExt_path() const{
    return (ext_path);
}

const std::string &LocationBlock::getAlias() const{
    return (alias);
}