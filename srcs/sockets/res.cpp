#include "../../includes/sockets/res.hpp"

int buildHtmlIndex(std::string &dir_name, std::vector<uint8_t> &body, size_t &body_len);

Mime Response::mime;

Response::Response() {
    response = "";
    file = "";
    body_length = 0;
    response_body = "";
    location = "";
    code = 0;
    auto_index = false;
    cgi = 0;
    cgi_resp = CGI();
}

Response::Response(Request &other) {
    request = other;
    response = "";
    file = "";
    body_length = 0;
    response_body = "";
    location = "";
    code = 0;
    auto_index = false;
    cgi = 0;
    cgi_resp = CGI();
}

Response::~Response() {}

void Response::clear() {
    response = "";
    file = "";
    body_length = 0;
    response_body = "";
    location = "";
    code = 0;
    auto_index = false;
}

bool Response::reqError() {
    if (request.error_code) {
        code = request.error_code;
        return true;
    }
    return false;
}

void Response::LocationMatch(const std::string& path, std::vector<LocationBlock> locations, std::string &key) {
    size_t biggest_match = 0;

    for (std::vector<LocationBlock>::const_iterator it = locations.begin(); it != locations.end(); ++it) {
        const std::string& locationPath = it->getPath();
        size_t locationPathLength = locationPath.length();
        if (path.find(locationPath) != 0) {
            continue;
        }
        bool isCompleteMatch = (locationPath == "/") ||
                               (path.length() == locationPathLength) ||
                               (path[locationPathLength] == '/');
        if (isCompleteMatch && locationPathLength > biggest_match) {
            biggest_match = locationPathLength;
            key = locationPath;
        }
    }
}

bool Response::isAllowedMethod(LocationBlock &location_temp, HttpMethod &method, short &code_temp) {
    std::vector<std::string> methods = location_temp.getMethods();
    std::string method_str;
    switch (method) {
        case 1: method_str = "GET"; break;
        case 2: method_str = "POST"; break;
        case 3: method_str = "DELETE"; break;
        default: method_str = ""; break;
    }
    bool found = false;
    for (std::vector<std::string>::iterator it = methods.begin(); it != methods.end(); ++it) {
        if (*it == method_str) {
            found = true;
            break;
        }
    }
    if (!found) {
        code_temp = 405;
        return true;
    }
    return false;
}

bool checkReturn(LocationBlock &loca, short &code, std::string &location) {
    if (!loca.getReturn().empty()) {
        location = loca.getReturn();
        code = 301;
        if (location[0] != '/')
            location.insert(location.begin(), '/');
        return true;
    }
    return false;
}

bool isDirectory(std::string &file) {
    struct stat st;
    if (stat(file.c_str(), &st) == 0) {
        if (st.st_mode & S_IFDIR)
            return true;
    }
    return false;
}

bool fileExists(std::string &file) {
    struct stat st;
    if (stat(file.c_str(), &st) == 0)
        return true;
    return false;
}

static std::string combinePaths(std::string p1, std::string p2, std::string p3)
{
    std::string res;
    int         len1;
    int         len2;

    len1 = p1.length();
    len2 = p2.length();
    if (p1[len1 - 1] == '/' && (!p2.empty() && p2[0] == '/') )
        p2.erase(0, 1);
    if (p1[len1 - 1] != '/' && (!p2.empty() && p2[0] != '/'))
        p1.insert(p1.end(), '/');
    if (p2[len2 - 1] == '/' && (!p3.empty() && p3[0] == '/') )
        p3.erase(0, 1);
    if (p2[len2 - 1] != '/' && (!p3.empty() && p3[0] != '/'))
        p2.insert(p1.end(), '/');
    res = p1 + p2 + p3;
    return (res);
}

bool Response::handleCGI(std::string &key) {
    std::string path = request.path;
    size_t len;

    if (path[0] && path[0] == '/')
        path.erase(0, 1);
    if (path == "cgi")
        path += "/" + server.getLocationKey(key)->getIndex();
    else if (path == "cgi/")
        path.append(server.getLocationKey(key)->getIndex());
    len = path.find('.');
    if (len == std::string::npos) {
        code = 501;
        return true;
    }
    std::string ext = path.substr(len);
    if (ext != ".py" && ext != ".sh") {
        code = 501;
        return true;
    }
    if (Config::getTypePath(path) != 1) {
        code = 404;
        return true;
    }
    if (access(path.c_str(), X_OK) == -1 || access(path.c_str(), R_OK) == -1) {
        code = 403;
        return true;
    }
    if (isAllowedMethod(*server.getLocationKey(key), request.method, code))
        return true;
    cgi_resp.clear();
    cgi_resp.path = path;
    cgi = 1;
    if (pipe(cgi_fd) == -1) {
        code = 500;
        return true;
    }
    cgi_resp.initEnv(request, server.getLocationKey(key));
    cgi_resp.execute(code);
    return false;
}

bool Response::handleTarget() {
    std::string key;
    LocationMatch(request.path, server.getLocations(), key);
    if (!key.empty()) {
        LocationBlock loca = *server.getLocationKey(key);
        if (isAllowedMethod(loca, request.method, code))
            return true;
        if (request.body.length() > loca.getClientMaxBodySize()) {
            code = 413;
            return true;
        }
        if (checkReturn(loca, code, location)) {
            return true;
        }
        if (loca.getPath().find("cgi") != std::string::npos) {
            return (handleCGI(key));
        }
        if (!loca.getAlias().empty())
            file = combinePaths(loca.getAlias(), request.path.substr(loca.getPath().length()), "");
        else
            file = combinePaths(server.getRoot(), request.path, "");
        if (isDirectory(file)) {
            if (file[file.length() - 1] != '/') {
                code = 301;
                location = request.path + "/";
                return true;
            }
            if (!loca.getIndex().empty())
                file += loca.getIndex();
            else
                file += server.getIndex();
            if (fileExists(file)) {
                if (loca.getAutoindex()) {
                    auto_index = true;
                    file.erase(file.find_last_of('/') + 1);
                    return false;
                }
                code = 404;
                return true;
            }
            if (isDirectory(file)) {
                code = 301;
                if (!loca.getIndex().empty())
                    location = combinePaths(request.path, loca.getIndex(), "");
                else
                    location = combinePaths(request.path, server.getIndex(), "");
                if (location[location.length() - 1] != '/')
                    location += "/";
                return true;
            }
        }
    }
    else {
        file = combinePaths(server.getRoot(), request.path, "");
        if (isDirectory(file)) {
            if (file[file.length() - 1] != '/') {
                code = 301;
                location = request.path + "/";
                return true;
            }
            file += server.getIndex();
            if (!fileExists(file)) {
                code = 403;
                return true;
            }
            if (isDirectory(file)) {
                code = 301;
                location = combinePaths(request.path, server.getIndex(), "");
                if (location[location.length() - 1] != '/')
                    location += "/";
                return true;
            }
        }
    }
    return false;
}

bool Response::readFile() {
    std::ifstream temp(file.c_str());
    if (temp.fail()) {
        code = 404;
        return false;
    }
    std::ostringstream str;
    str << temp.rdbuf();
    response_body = str.str();
    return true;
}

bool Response::buildBody() {
    if (request.body.length() > server.getClientMaxBodySize()) {
        code = 413;
        return true;
    }
    if (handleTarget())
        return true;
    if (cgi || auto_index)
        return false;
    if (code)
        return false;

    if (request.method == GET) {
        if (!readFile())
            return true;
    }
    else if (request.method == POST) {
        std::ofstream temp(file.c_str(), std::ios::binary);
        if (temp.fail()) {
            code = 404;
            return true;
        }
        else
            temp.write(request.body.c_str(), request.body.length());
    }
    else if (request.method == DELETE) {
        if (!fileExists(file)) {
            code = 404;
            return true;
        }
        if (remove(file.c_str()) != 0) {
            code = 500;
            return true;
        }
    }
    code = 200;
    return false;
}

std::string Response::getErrorPage() const {
    return ("<html>\r\n<head><title>" + to_string(code) + " " +
            statusCodeString(code) + " </title></head>\r\n" + "<body>\r\n" +
            "<center>\r\n<h1>" + to_string(code) + " " + statusCodeString(code) +
            "</h1>\r\n</center>\r\n" + "</body>\r\n</html>\r\n");
}

std::string Response::readErrorPage(const std::string &filename) {
    std::fstream file(filename.c_str());
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

void Response::setDefaultErrorPages() {
    const std::map<int, std::string> &error_pages = server.getErrorPages();
    const std::map<int, std::string>::const_iterator &it = error_pages.find(code);

    if (it != error_pages.end() && !it->second.empty())
        response_body = readErrorPage(server.getRoot() + it->second);
    else
        response_body = getErrorPage();
}

void Response::buildErrorBody() {
    if (!server.getErrorPages().count(code) ||
        !server.getErrorPages().at(code).empty() ||
        request.method == DELETE || request.method == POST)
        setDefaultErrorPages();
    else {
        if (code >= 400 && code < 599) {
            location = server.getErrorPages().at(code);
            if (location[0] != '/')
                location.insert(location.begin(), '/');
            code = 302;
        }
        file = server.getRoot() + server.getErrorPages().at(code);
        short old_code = code;
        if (!readFile()) {
            code = old_code;
            setDefaultErrorPages();
        }
    }
}

void Response::createResponse() {
    if (reqError() || buildBody())
        buildErrorBody();
    if (cgi)
        return ;
    if (auto_index) {
        if (buildHtmlIndex(file, body, body_length)) {
            code = 500;
            buildErrorBody();
            return ;
        }
        else
            code = 200;
        response_body.insert(response_body.begin(), body.begin(), body.end());
    }
    response.append("HTTP/1.1 " + to_string(code) + " ");
    response.append(statusCodeString(code) + "\r\n");
    response.append("Content-Type: ");
    if (file.find('.') != std::string::npos)
        response.append(mime.mime_types[file.substr(file.find_last_of('.'))] + "\r\n");
    else
        response.append("text/html\r\n");
    response.append("Content-Length: " + to_string(response_body.length()) + "\r\n");
    if (request.headers.find("Cookie") != request.headers.end())
        response.append("Set-Cookie: " + request.headers["Cookie"] + "\r\n");
    if (request.headers["Connection"] == "keep-alive")
        response.append("Connection: " + request.headers["Connection"] + "\r\n");
    else
        response.append("Connection: close\r\n");
    response.append("Server: " + request.headers["User-Agent"] + "\r\n");
    if (!location.empty())
        response.append("Location: " + location + "\r\n");
    char date[100];
    time_t now = time(0);
    strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S GMT", gmtime(&now));
    response.append("Date: " + std::string(date) + "\r\n");
    response.append("\r\n");
    if (request.method == GET || code != 200)
        response.append(response_body);
}
