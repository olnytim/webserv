#include "../../includes/request/Request.hpp"

const std::string &Request::getRequestTarget() const{
	return requestTarget;
}


const std::string &Request::getMethod() const{
	return method;
}

void Request::setMethod(const std::string &str){
	method = str;
}

void Request::setRequestTarget(const std::string &str){
	requestTarget = str;
}

