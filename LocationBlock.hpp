#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include "IReportError.hpp"

class LocationBlock : public IReportError{
public:
	LocationBlock();

	void reportError() const;

	void callFunction(const std::string &key, const std::string &str);
	void setRedirect_map(std::string line);
	void setRoot(std::string line);
	void setMethods(std::string line);
	void setIndex(std::string line);
	void setAutoindex(std::string line);
	void setRoute_to_be_saved(std::string line);
	void setClient_body_temp_path(std::string line);
	void setClient_max_body_size(std::string line);
	void setCgi_pass(std::string line);

//	void setAllowed_methods(std::string line);
private:
	std::map<std::string, void(LocationBlock::*)(std::string)> keywordsMap;
	std::map<short, std::string> redirect_map;
	std::string root;
	std::vector<std::string> methods;
	std::string index;
	bool autoindex;
	std::string route_to_be_saved;
	std::string client_body_temp_path;
	unsigned int client_max_body_size;
	std::string cgi_pass;

//	std::vector<std::string> allowed_methods; //not sure if i have to implement this one :D
};