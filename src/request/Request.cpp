#include "../../includes/request/Request.hpp"

void Request::checkMethod(){
	
}

void Request::parseRequestLine(const std::string &reqLine){
	if (!reqLine){
		std::cout << "Error" << std::endl; //throw error
		return ;
	}
	std::stringstream req(reqLine);
	getline(req, method);
	checkMethod();
}

void Request::parse(const std::string &request){
	parseRequestLine(request.substr(0, request.find("\n")));
}

const std::string &Request::getRequestLine() const{
	return requestLine;
}

void Request::setRequestLine(const std::string &str){
	requestLine = str;
}
