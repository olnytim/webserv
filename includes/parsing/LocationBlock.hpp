#pragma once

//#include <iostream>
//#include <map>
//#include <vector>
//#include <sstream>
#include "IReportError.hpp"
#include "exceptions.hpp" 
#include "../Utils.hpp"

class LocationBlock{
public:
	LocationBlock();

	static void reportError(const ParseException &ex) ;

	void callFunction(const std::string &key, const std::string &str);
	void setRedirect_map(const std::string& line);
	void setRoot(const std::string& line);
	void setMethods(const std::vector<std::string>& line);
	void setIndex(const std::string& line);
	void setAutoindex(const std::string& line);
	static void setRoute_to_be_saved(const std::string& line);
	void setClient_body_temp_path(const std::string& line);
	void setClient_max_body_size(const std::string& line);
    void setCgi_path(const std::vector<std::string>& path);
    void setCgi_extension(const std::vector<std::string>& extension);
    void setReturn_value(const std::string& line);
    void setPath(const std::string& line);
    void setAlias(const std::string& line);

    const std::string &getRoot() const;
    const std::string &getPath() const;
    const std::string &getIndex() const;
    const std::string &getRoute_to_be_saved() const;
    const std::string &getClient_body_temp_path() const;
    const std::vector<std::string> &getCgi_path() const;
    const std::vector<std::string> &getCgi_extension() const;
    const std::string &getReturn_value() const;
    const std::vector<std::string> &getMethods() const;
    const std::map<short, std::string> &getRedirect_map() const;
    unsigned int getClient_max_body_size() const;
    bool getAutoindex() const;
    const std::map<std::string, std::string> &getExt_path() const;
    const std::string &getAlias() const;

//	void setAllowed_methods(const std::string& line);
    std::map<std::string, std::string> ext_path;
private:
    typedef void(LocationBlock::*func)(const std::string&);
    std::map<std::string, func> keywordsMap;
    std::map<short, std::string> redirect_map;

    std::vector<std::string> methods;
    std::vector<std::string> cgi_path;
    std::vector<std::string> cgi_extension;

    std::string path;
    std::string root;
    std::string index;
    std::string return_value;
    std::string route_to_be_saved;
    std::string client_body_temp_path;
    std::string alias;

    unsigned int client_max_body_size;
    bool autoindex;

//	std::vector<std::string> allowed_methods; //not sure if i have to implement this one :D
};
