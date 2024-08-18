#pragma once

//#include <iostream>
//#include <map>
//#include <vector>
//#include <sstream>
#include "exceptions.hpp"
#include "../Headers.hpp"

class LocationBlock{
public:
	LocationBlock();

	static void reportError(const ParseException &ex) ;

	void callFunction(const std::string &key, const std::string &str);
	void setRedirect_map(const std::string& line);
	void setRoot(const std::string& line);
	void setMethods(const std::string& line);
	void setIndex(const std::string& line);
	void setAutoindex(const std::string& line);
	static void setRoute_to_be_saved(const std::string& line);
	void setClient_body_temp_path(const std::string& line);
	void setClient_max_body_size(const std::string& line);
	void setCgi_pass(const std::string& line);

    const std::string &getRoot() const;
    const std::string &getIndex() const;
    const std::string &getRoute_to_be_saved() const;
    const std::string &getClient_body_temp_path() const;
    const std::string &getCgi_pass() const;
    const std::vector<std::string> &getMethods() const;
    const std::map<short, std::string> &getRedirect_map() const;
    unsigned int getClient_max_body_size() const;
    bool getAutoindex() const;

//	void setAllowed_methods(const std::string& line);
private:
	typedef void(LocationBlock::*func)(const std::string&);
	std::map<std::string, func> keywordsMap;
	std::map<short, std::string> redirect_map;

	std::vector<std::string> methods;

	std::string root;
	std::string index;
	std::string route_to_be_saved;
	std::string client_body_temp_path;
	std::string cgi_pass;

	unsigned int client_max_body_size;
	bool autoindex;

//	std::vector<std::string> allowed_methods; //not sure if i have to implement this one :D
};
