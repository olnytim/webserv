#include "../../includes/parsing/ServerBlock.hpp"
#include "../../includes/parsing/config.hpp"

ServerBlock::ServerBlock() {
	keywords["server_name"] = &ServerBlock::setServerName;
	keywords["port"] = &ServerBlock::setPort;
	keywords["client_max_body_size"] = &ServerBlock::setClientMaxBodySize;
	keywords["listen"] = &ServerBlock::setListen;
	keywords["error_page"] = &ServerBlock::addErrorPage;

    client_max_body_size = MAX_CONTENT_LENGTH;
    port = 0;
    host = 0;
    server_name = "";
    root = "";
    index = "";
    autoindex = false;
    listen_fd = -1;
    error_pages[400] = "";
    error_pages[401] = "";
    error_pages[403] = "";
    error_pages[404] = "";
    error_pages[405] = "";
    error_pages[500] = "";
    error_pages[501] = "";
    error_pages[502] = "";
    error_pages[503] = "";
    error_pages[504] = "";
    error_pages[505] = "";
}

void ServerBlock::checkToken(std::string &param) const {
    size_t pos = param.rfind(";");
    if (pos != param.length() - 1)
        reportError(locationParseException("Invalid token in Server Block"));
    param.erase(pos);
}

void ServerBlock::reportError(const ParseException &ex) const{
	throw (ex);
}

bool ServerBlock::checkLocations() const{
    if (locations.size() < 2)
        return (false);
    std::vector<LocationBlock>::const_iterator it1 = locations.begin();
    std::vector<LocationBlock>::const_iterator it2;
    for (it1; it1 != locations.end(); ++it1){
        for (it2 = it1 + 1; it2 != locations.end(); ++it2){
            if (it1->getPath() == it2->getPath())
                return (true);
        }
    }
    return (false);
}

const std::vector<std::string> &ServerBlock::getLocationsTxt() const{
	return (locationsTxt);
}

void ServerBlock::callFunction(const std::string &key, std::string str){
	typedef void (ServerBlock::*MemberFuncType)(const std::string&);
	MemberFuncType func = keywords[key];
	if (!func || str.size() == 0){
		reportError(locationParseException("Invalid keyword or content for keyword in Server Block"));
	}
	(this->*func)(const_cast<const std::string&>(str));
}

void ServerBlock::setServerNames(const std::string &line){
	std::stringstream ss(line);
	std::string tmp;
	while (getline(ss, tmp, ' ')){
		server_names.push_back(tmp);
	}
}

void ServerBlock::setServerName(const std::string &line) {
    checkToken(const_cast<std::string &>(line));
    server_name = line;
}

void ServerBlock::setHost(std::string &line) {
    checkToken(const_cast<std::string &>(line));
    if (line == "localhost")
        line = "127.0.0.1";
    if (!isValidHost(line))
        reportError(serverParseException("Invalid Host in ServerBlock"));
    host = inet_addr(line.data());
}

void ServerBlock::setRoot(const std::string &line) {
    checkToken(const_cast<std::string &>(line));
    if (ConfigFile::getTypePath(line) == 2) {
        root = line;
        return;
    }
    char dir[PATH_MAX];

    std::string tmp = getcwd(dir, PATH_MAX) + line;
    if (ConfigFile::getTypePath(tmp) != 2)
        reportError(serverParseException("Invalid Root in ServerBlock"));
    root = tmp;
}

void ServerBlock::setPort(const std::string &line) {
    checkToken(const_cast<std::string &>(line));
    for (size_t i = 0; i < line.size(); i++) {
        if (!isdigit(line[i]))
            reportError(serverParseException("Invalid Port in ServerBlock"));
    }
    port = std::stoi(line);
    if (port < 0 || port > 65535)
        reportError(serverParseException("Invalid Port in ServerBlock"));
    port = (uint16_t)port;
}

void ServerBlock::setClientMaxBodySize(const std::string &line) {
    checkToken(const_cast<std::string &>(line));
    for (size_t i = 0; i < line.size(); i++) {
        if (!isdigit(line[i]))
            reportError(serverParseException("Invalid Port in ServerBlock"));
    }
    if (!(client_max_body_size = ft_stoi(line)))
        reportError(serverParseException("Invalid Client max body size in ServerBlock"));
}

void ServerBlock::addErrorPage(const std::string &line){
	std::string error_num = line.substr(0, line.find(" "));
	std::string error_page = line.substr(line.find(" ") + 1);
	std::istringstream iss(error_num);
	unsigned short key;
	if (!(iss >> key)){
		reportError(serverParseException("Invalid Error page value in ServerBlock"));
	}
	error_pages[key] = error_page;
}

void ServerBlock::setErrorPages(const std::vector<std::string> &line){
    if (line.empty())
        return ;
    if (line.size() % 2 != 0)
        reportError(serverParseException("Invalid Error page value in ServerBlock"));
    for (size_t i = 0; i < line.size() - 1; ++i){
        for (size_t j = 0; j < line[i].size(); j++){
            if (!isdigit(line[i][j]))
                reportError(serverParseException("Invalid Error page value in ServerBlock"));
        }
        if (line[i].size() != 3)
            reportError(serverParseException("Invalid Error page value in ServerBlock"));
        short key = ft_stoi(line[i]);
        if (statusCodeString(key) == "Unknown Status Code" || key < 400)
            reportError(serverParseException("Invalid Error page value in ServerBlock"));
        ++i;
        std::string path = line[i];
        checkToken(const_cast<std::string &>(path));
        if (ConfigFile::getTypePath(path) != 2) {
            if (ConfigFile::getTypePath(root + path) != 1)
                reportError(serverParseException("Invalid Error page value in ServerBlock"));
            if (access((root + path).c_str(), R_OK) == -1 || access((root + path).c_str(), F_OK) == -1)
                reportError(serverParseException("Error page file is not accessible"));
        }
        std::map<unsigned short, std::string>::iterator it = error_pages.find(key);
        if (it != error_pages.end())
            error_pages[key] = path;
        else
            error_pages.insert(std::make_pair(key, path));
    }
}

void ServerBlock::setListen(const std::string &line){
	listen = line;
}

void ServerBlock::setAutoindex(const std::string &line){
    checkToken(const_cast<std::string &>(line));
    if (line == "on")
        autoindex = true;
    else if (line == "off")
        autoindex = false;
    else
        reportError(serverParseException("Invalid Autoindex value in ServerBlock"));
}

void ServerBlock::setIndex(const std::string &line) {
    checkToken(const_cast<std::string &>(line));
    index = line;
}

void ServerBlock::setFd(int fd) {
    listen_fd = fd;
}

void ServerBlock::addLocationTxt(std::string str){
	locationsTxt.push_back(str);
}

void ServerBlock::parseLocations(){
	std::string line;
	std::string key;

	for (size_t i = 0; i < locationsTxt.size(); i++){
		std::stringstream ss(locationsTxt[i]);
		while (getline(ss, line, ';')){
			size_t pos = ConfigFile::skipWhitespace(line, 0);
			if (pos == line.size())
				break ;
			key = line.substr(pos , line.find(' ', pos) - pos);
			locations[i].callFunction(key, line.substr(line.find(' ', pos) + 1));
		}
	}
}

void ServerBlock::addLocation(const LocationBlock &loc){
	locations.push_back(loc);
}

const std::vector<std::string> &ServerBlock::getServerNames() const{
    return (server_names);
}

const std::vector<LocationBlock> &ServerBlock::getLocations() const{
    return (locations);
}

const std::map<unsigned short, std::string> ServerBlock::getErrorPage() const{
    return (error_pages);
}

std::string ServerBlock::getListen() const{
    return (listen);
}

unsigned short ServerBlock::getPort() const{
    return (port);
}

unsigned int ServerBlock::getClientMaxBodySize() const{
    return (client_max_body_size);
}

const std::string &ServerBlock::getServerName() const{
    return (server_name);
}

in_addr_t ServerBlock::getHost() const{
    return (host);
}

const std::string &ServerBlock::getRoot() const{
    return (root);
}

const std::string &ServerBlock::getIndex() const{
    return (index);
}

bool ServerBlock::getAutoindex() const{
    return (autoindex);
}

int ServerBlock::getFd() const {
    return (listen_fd);
}

void ServerBlock::setupServer(){
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        reportError(serverParseException("Socket creation failed in ServerBlock"));

    int value = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int));
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = host;
    server_address.sin_port = htons(port);
    if (bind(listen_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        reportError(serverParseException("Bind failed in ServerBlock"));
}

bool ServerBlock::isValidHost(std::string host) const {
    struct sockaddr_in sa;
    int res = inet_pton(AF_INET, host.data(), &(sa.sin_addr));
    return (res != 0);
}

bool ServerBlock::isValidErrorPages() {
    std::map<unsigned short, std::string>::iterator it = error_pages.begin();
    for (it; it != error_pages.end(); ++it) {
        if (it->first < 100 || it->first > 599)
            return (false);
    }
    return (true);
}

int ServerBlock::isValidLocation(LocationBlock &location) const {
    if (location.getPath() == "/cgi-bin") {
        if (location.getCgi_path().empty() || location.getCgi_extension().empty())
            return (1);
        if (access(location.getIndex().c_str(), F_OK) < 0) {
            std::string path = location.getRoot() + location.getPath() + "/" + location.getIndex();
            if (ConfigFile::getTypePath(path) != 1) {
                std::string root = getcwd(NULL, 0);
                location.setRoot(root);
                path = root + location.getPath() + "/" + location.getIndex();
            }
            if (path.empty() || ConfigFile::getTypePath(path) != 1 || access(path.c_str(), F_OK) < 0)
                return (1);
        }
        if (location.getCgi_path().size() != location.getCgi_extension().size())
            return (1);
        std::vector<std::string>::const_iterator it1 = location.getCgi_path().begin();
        std::vector<std::string>::const_iterator it2 = location.getCgi_extension().begin();
        for (it1; it1 != location.getCgi_path().end(); ++it1) {
            if (ConfigFile::getTypePath(*it1) != 1)
                return (1);
//            if (access(it1->c_str(), F_OK) < 0 || access(it2->c_str(), F_OK) < 0)
//                return (1);
        }
        for (it1 = location.getCgi_extension().begin(); it1 != location.getCgi_extension().end(); ++it1) {
            std::string tmp = *it1;
            if (tmp != ".py" && tmp != ".sh")
                return (1);
            for (it2 = location.getCgi_path().begin(); it2 != location.getCgi_path().end(); ++it2) {
                std::string tmp_path = *it2;
                if (tmp == ".py")
                    if (tmp_path.find("python") != std::string::npos)
                        location.ext_path.insert(std::make_pair(".py", tmp_path));
                else if (tmp == ".sh")
                    if (tmp_path.find("bash") != std::string::npos)
                        location.ext_path.insert(std::make_pair(".sh", tmp_path));
            }
        }
        if (location.getCgi_path().size() != location.getExt_path().size())
            return (1);
    }
    else {
        if (location.getPath()[0] != '/')
            return (2);
        if (location.getRoot().empty())
            location.setRoot(root);
        if (!location.getReturn_value().empty())
            if (ConfigFile::ifFileExistAndReadable(location.getRoot(), location.getReturn_value()))
                return (3);
        if (!location.getAlias().empty())
            if (ConfigFile::ifFileExistAndReadable(location.getRoot(), location.getAlias()))
                return (4);
        if (ConfigFile::ifFileExistAndReadable(location.getRoot() + location.getPath() + "/", location.getIndex()))
            return (5);
    }
    return (0);
}