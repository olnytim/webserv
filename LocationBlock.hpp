#pragma once

#include <iostream>
#include <map>
#include <vector>

class LocationBlock{
public:
	LocationBlock();

	void callFunction(const std::string &key, const std::string &str);
	void setAutoindex(std::string line);
	void setRedirect_map(std::string line);
	void setRoot(std::string line);
	void setMethods(std::string line);
	void setAllowed_methods(std::string line);
	void setIndex(std::string line);
	void setAutoindex(std::string line);
	void setRoute_to_be_saved(std::string line);
	void setClient_body_temp_path(std::string line);
	void setClient_max_body_size(std::string line);
	void setCgi_pass(std::string line);
private:
	enum e_methods{
		E_GET,
		E_POST,
	};
	std::map<std::string, void(LocationBlock::*)(std::string)> keywordsMap;
	std::map<short, std::string> redirect_map; //return 
	std::string root; //root
	std::vector<e_methods> methods; //methods
	std::vector<e_methods> allowed_methods; //limit_except <methods> {deny all}
	std::string index; // index
	bool autoindex; // autoindex
	std::string route_to_be_saved; // location /<route>
	std::string client_body_temp_path; // client_body_temp_path
	unsigned int client_max_body_size; // client_map_body_size
	std::string cgi_pass;
};
