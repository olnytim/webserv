#include "../../includes/request/Request.hpp"

//Getters

const std::string &Request::getRequestTarget() const{
	return requestTarget;
}


const std::string &Request::getMethod() const{
	return method;
}

const std::string &Request::getVersion() const{
	return version;
}

const std::string &Request::getHeadersMap() const{
	return headersMap;
}


//Setters

void Request::setMethod(const std::string &str){
	method = str;
}

void Request::setRequestTarget(const std::string &str){
	requestTarget = str;
}

void Request::setVersion(const std::string &version){
	this->version = version;
}

void Request::setHeadersMap(const std::map<std::string, std::string> &headersMap){
	this->headersMap = headersMap;
}