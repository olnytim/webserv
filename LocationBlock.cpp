#include <LocationBlock.hpp>

LocationBlock::LocationBlock(){
	keywordsMap["return"] = &LocationBlock::setRedirect_map;
	keywordsMap["root"] = &LocationBlock::setRoot;
	keywordsMap["methods"] = &LocationBlock::setMethods;
	keywordsMap["limit_except"] = &LocationBlock::setAllowed_methods;
	keywordsMap["index"] = &LocationBlock::setIndex;
	keywordsMap["autoindex"] = &LocationBlock::setAutoindex;
	keywordsMap["client_body_temp_path"] = &LocationBlock::setClient_body_temp_path;
	keywordsMap["client_max_body_size"] = &LocationBlock::setClient_max_body_size;
}

void LocationBlock::callFunction(const std::string &key, const std::string &str){
	typedef void (LocationBlock::*MemberFuncType)(std::string);
	MemberFuncType func = keywords[key];
	if (!func || str.size() == 0){
		//Throw exception omaygot
	}
	(this->*func)(str);
}

void LocationBlock::setAutoindex(std::string line){
	if (line == "on"){
		autoindex = true;
	} else if (line == "off"){
		autoindex = false;
	} else{
		//throw error
	}
}
	
void LocationBlock::setRedirect_map(std::string line){

}

void LocationBlock::setRoot(std::string line){

}
	
void LocationBlock::setMethods(std::string line){
	std::stringstream ss(line);

	while (getline(ss, ' '))
		methods.push_back();
}

void LocationBlock::setAllowed_methods(std::string line){

}

void LocationBlock::setIndex(std::string line){
	index = line;
}

void LocationBlock::setRoute_to_be_saved(std::string line){

}

void LocationBlock::setClient_body_temp_path(std::string line){

}
void LocationBlock::setClient_max_body_size(std::string line){

}