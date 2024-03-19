#include "../includes/config.hpp"

void ConfigFile::reportError(const ParseException &ex) const{
	throw (ex);
}

void ConfigFile::openConfig(){
	this->config.open("test.conf");
	if (!config.is_open()){
		reportError(configFileException("Could not open the config file"));
	}
}

size_t ConfigFile::skipWhitespace(const std::string &line, size_t pos){
	while (pos < line.size() && (line[pos] == ' ' || line[pos] == '	' || line[pos] == '\n'))
		pos++;
	return (pos);
}

size_t ConfigFile::findPair(const std::string &line, size_t pos) const{
	if (pos >= line.size())
		reportError(configFileException("Invalid configuration"));
	while (line[pos] != '}'){
		if (pos >= line.size()){
			reportError(configFileException("Invalid configuration"));
		}
		if (line[pos] == '{'){
			pos = findPair(line, pos + 1);
		}
		pos++;
	}
	return (pos);
}

void ConfigFile::divideIntoServers(const std::string &line) {
	size_t pos1 = 0;
	size_t pos2 = 0;

	while ((pos1 = line.find("server", pos1)) != std::string::npos){
		pos1 += 6;
		pos1 = skipWhitespace(line, pos1);
		if (pos1 < line.size() && line[pos1] == '{'){
			pos2 = findPair(line, ++pos1);
			serversTxt.push_back(line.substr(pos1, pos2 - pos1));
			pos1 = skipWhitespace(line, pos2 + 1);
		} else
			reportError(configFileException("Invalid configuration"));
	}
}

void ConfigFile::removeComments(std::string &line) {
	size_t pos;
	std::string line1;
	std::string line2;

	while ((pos = line.find('#')) != std::string::npos){
		line1 = line.substr(0, pos - 1);
		line2 = line.substr(line.find('\n', pos));
		line = line1 + line2;
	}
}

void ConfigFile::cutLocations(){

	for(size_t i = 0; i < serversTxt.size(); i++){
		ServerBlock server;
		size_t pos1 = 0;
		size_t pos2 = 0;
		size_t pos3 = 0;

		while ((pos1 = serversTxt[i].find("location", pos1)) != std::string::npos){
			LocationBlock loc;
			pos3 = pos1;
			pos1 += 8;
			pos1 = skipWhitespace(serversTxt[i], pos1);
			if (pos1 < serversTxt[i].size() && serversTxt[i][pos1] == '/'){
				loc.setRoute_to_be_saved(serversTxt[i].substr(pos1, serversTxt[i].find(' ', pos1) - pos1));
				pos1 = serversTxt[i].find(' ', pos1);
			}
			pos1 = skipWhitespace(serversTxt[i], pos1);
			if (pos1 < serversTxt[i].size() && serversTxt[i][pos1] == '{'){
				pos2 = findPair(serversTxt[i], ++pos1);
				server.addLocationTxt(serversTxt[i].substr(pos1, pos2 - pos1));
				server.addLocation(loc);
				pos1 = skipWhitespace(serversTxt[i], pos2 + 1);
			} else
				reportError(configFileException("Invalid configuration"));
			std::string first = serversTxt[i].substr(0, pos3);
			std::string second = serversTxt[i].substr(pos1);
			serversTxt[i] = first + second;
		}
		servers.push_back(server);
	}
}

void ConfigFile::parseServers(){
	cutLocations();
	std::string line;
	std::string key;

	if (serversTxt.size() < 1)
		reportError(configFileException("No server configuration in the config file"));
	for (size_t i = 0; i < serversTxt.size(); i++){
		std::stringstream ss(serversTxt[i]);
		while (getline(ss, line, ';')){
			size_t pos = skipWhitespace(line, 0);
			if (pos == line.size())
				break ;
			key = line.substr(pos , line.find(' ', pos) - pos);
			servers[i].callFunction(key, line.substr(line.find(' ', pos) + 1));
		}
		servers[i].parseLocations();
	}

}

void ConfigFile::parse(){
	std::string line;

	getline(config, line, '\0');
	try{
		removeComments(line);
	}	catch (const std::out_of_range &e){
		std::cout << e.what() << std::endl;
	}
	divideIntoServers(line);
	parseServers();
}

void ConfigFile::printParsing() {
    for (size_t i = 0; i < servers.size(); i++) {
        std::cout << "Server " << i << std::endl;
        std::cout << "Server names: ";
        for (size_t j = 0; j < servers[i].getServerNames().size(); j++) {
            std::cout << servers[i].getServerNames()[j] << " ";
        }
        std::cout << std::endl;
        std::cout << "Listen: " << servers[i].getListen() << std::endl;
        std::cout << "Port: " << servers[i].getPort() << std::endl;
        std::cout << "Error pages: " << std::endl;
        std::map<unsigned short, std::string> error_pages = servers[i].getErrorPage();
        for (std::map<unsigned short, std::string>::iterator it = error_pages.begin(); it != error_pages.end(); it++) {
            std::cout << it->first << " " << it->second << std::endl;
        }
        std::cout << "Client max body size: " << servers[i].getClientMaxBodySize() << std::endl;
        std::cout << "Locations: " << std::endl;
        std::vector<LocationBlock> locations = servers[i].getLocations();
        for (size_t j = 0; j < locations.size(); j++) {
            std::cout << "Location " << j << std::endl;
            std::cout << "Route to be saved: " << locations[j].getRoute_to_be_saved() << std::endl;
            std::cout << "Root: " << locations[j].getRoot() << std::endl;
            std::cout << "Index: " << locations[j].getIndex() << std::endl;
            std::cout << "Autoindex: " << locations[j].getAutoindex() << std::endl;
            std::cout << "Client body temp path: " << locations[j].getClient_body_temp_path() << std::endl;
            std::cout << "Client max body size: " << locations[j].getClient_max_body_size() << std::endl;
            std::cout << "Cgi pass: " << locations[j].getCgi_pass() << std::endl;
            std::cout << "Methods: ";
            std::vector<std::string> methods = locations[j].getMethods();
            for (size_t k = 0; k < methods.size(); k++) {
                std::cout << methods[k] << " ";
            }
        }
        std::cout << std::endl;
    }
}