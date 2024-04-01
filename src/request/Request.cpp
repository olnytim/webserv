#include "../../includes/request/Request.hpp"

RequestParsing::RequestParsing(Request &request) : req(request){
}

void RequestParsing::requestTarget(std::stringstream &req){

}

void RequestParsing::method(std::stringstream &req){
	std::string reqTarget;
	getline(req, reqTarget, ' ');

}

void RequestParsing::parseRequestLine(const std::string &reqLine, Request &ref){
	std::string method;

	if (!reqLine.size()){
		std::cout << "Error" << std::endl; //throw error
		return ;
	}
	method();
	std::stringstream req(reqLine);
	getline(req, method, ' ');
	if (!method.size()){
		std::cout << "Error" << std::endl; //throw error
		return ;
	}

}

void RequestParsing::parse(const std::string &request){
	parseRequestLine(request.substr(0, request.find("\n")), *this);
}

const std::string &Request::getRequestLine() const{
	return requestLine;
}

void Request::setRequestLine(const std::string &str){
	requestLine = str;
}
