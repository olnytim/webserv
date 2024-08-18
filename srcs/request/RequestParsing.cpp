#include "../../includes/request/RequestParsing.hpp"

RequestParsing::RequestParsing(Request &request) : request(request){
}

void RequestParsing::httpVersion(std::stringstream &req){
	std::string version;

	getline(req, version);
	if (version.empty() || version != "HTTP/1.1"){
		std::cout << "Error" << std::endl; //throw error
		return ;
	}
	request.setVersion(version);
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

void RequestParsing::parseBody(const std::string &body){

}

void RequestParsing::parseHeaders(const std::string &headers){
	std::stringstream headersStream(headers);
	std::string currentHeader;
	std::map<std::string, std::string> headersMap;
	
	while (getline(headersStream, currentHeader)){
		int delimiterIndex = currentHeader.find(':');
		std::string headerName = currentHeader.substr(0, delimiterIndex);
		std::string headerContent = currentHeader.substr(delimiterIndex, currentHeader.size() - delimiterIndex);
		headersMap[headerName] = headerContent;
	}
	request.setHeadersMap(headersMap);
}

void RequestParsing::parse(const std::string &request){
	typedef void(RequestParsing::*func)(const std::string&);
	func parseFunctions[3] = {
	 &RequestParsing::parseRequestLine, 
	 &RequestParsing::parseHeaders, 
	 &RequestParsing::parseBody
	};

	std::stringstream reqStream(request);
	std::string currentLine;

	for (int i = 0; i < 3; i++){
		if (getline(reqStream, currentLine)){
			(this->*parseFunctions[i])(currentLine);
		} else {
			std::cout << "Error" << std::endl;
			return;
		}
	}
}