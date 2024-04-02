#include "../../includes/request/RequestParsing.hpp"

RequestParsing::RequestParsing(Request &request) : request(request){
}

void RequestParsing::httpVersion(std::stringstream &req){
	std::string version;

	getline(req, version);
	
}

void RequestParsing::requestTarget(std::stringstream &req){
	std::string reqTarget;
	getline(req, reqTarget, ' ');
	if (!reqTarget.size()){
		std::cout << "Error" << std::endl; //throw error
		return ;
	}
	request.setRequestTarget(reqTarget);
}

void RequestParsing::method(std::stringstream &req){
	std::string method;
	getline(req, method, ' ');
	if (!method.size()){
		std::cout << "Error" << std::endl; //throw error
		return ;
	}
	request.setMethod(method);
}

void RequestParsing::parseRequestLine(const std::string &reqLine){

	if (!reqLine.size()){
		std::cout << "Error" << std::endl; //throw error
		return ;
	}
	std::stringstream req(reqLine);
	method(req);
	requestTarget(req);

}

void RequestParsing::parse(const std::string &request){
	parseRequestLine(request.substr(0, request.find("\n")));
}