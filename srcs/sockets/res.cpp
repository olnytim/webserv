#include "../../includes/sockets/res.hpp"

Mime Response::mime;

Response::Response() {
    response = "";
    file = "";
    body_length = 0;
    response_body = "";
    location = "";
    code = 0;
    // res = nullptr;
    res = NULL;
    auto_index = false;
}

Response::Response(Request &other) {
    request = other;
    response = "";
    file = "";
    body_length = 0;
    response_body = "";
    location = "";
    code = 0;
    // res = nullptr;
    res = NULL;
    auto_index = false;
}

Response::~Response() {
}

bool Response::reqError() {
    // check if error code is set
//    if (request.error_code) {
//        code = request.error_code;
//        return true;
//    }
    return false;
}

void Response::LocationMatch(const std::string& path, std::vector<LocationBlock> locations, std::string &key) {
    size_t temp = 0;

    for (std::vector<LocationBlock>::iterator it = locations.begin(); it != locations.end(); ++it) {
        if (path.find(it->getPath()) == 0) {
            if (it->getPath() == "/" || path.length() == it->getPath().length() || path[it->getPath().length()] == '/') {
                if (it->getPath().length() > temp) {
                    temp = it->getPath().length();
                    key = it->getPath();
                }
            }
        }
    }
}

bool Response::isAllowedMethod(HttpMethod &method, LocationBlock &location, short &code) {
    std::vector<std::string> methods = location.getMethods();
    (void) code;
    // Определяем строковое представление метода
    std::string method_str;
    switch (method) {
        case GET: method_str = "GET"; break;
        case POST: method_str = "POST"; break;
        case DELETE: method_str = "DELETE"; break;
        case PUT: method_str = "PUT"; break;
        case HEAD: method_str = "HEAD"; break;
        default: method_str = ""; break;
    }

    // Проверяем, содержится ли метод в списке разрешённых
    // if (std::find(methods.begin(), methods.end(), method_str) == methods.end()) {
    //     code = 405;  // Метод не разрешён
    //     return true;
    // }

    return false;  // Метод разрешён
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

bool Response::handleTarget() {
    std::string key;
    LocationMatch(request.path, server.getLocations(), key);
    if (key.length() > 0) {
        LocationBlock loca = *server.getLocationKey(key);
        if (isAllowedMethod(request.method, loca, code))
            return true;
        if (request.body.length() > loca.getClientMaxBodySize()) {
            code = 413;
            return true;
        }
        if (checkReturn(loca, code, location))
            return true;
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
            if (!fileExists(file)) {
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
    if (code)
        return false;
    if (request.method == GET || request.method == HEAD) {
        if (!readFile())
            return true;
    }
    else if (request.method == POST || request.method == PUT) {
        if (fileExists(file) && request.method == PUT) {
            code = 204;
            return false;
        }
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

void Response::buildErrorBody() {
    ;
}

void Response::createResponse() {
    if (buildBody() || reqError())
        buildErrorBody();
    printf("Body: %s\n", body.data());
    /* Set State */
    // response.append("HTTP/1.1 " + std::to_string(code) + " ");
    response.append(statusCodeString(code) + "\r\n");

    /* Set Type */
    response.append("Content-Type: ");
    if (file.find('.') != std::string::npos)
        response.append(mime.mime_types[file.substr(file.find_last_of('.'))] + "\r\n");
    else
        response.append("text/html\r\n");

    /* Set Length */
    // response.append("Content-Length: " + std::to_string(response.length()) + "\r\n");

    /* Set Connection */
    if (request.headers["Connection"] == "keep-alive")
        response.append("Connection: " + request.headers["Connection"] + "\r\n");
    else
        response.append("Connection: close\r\n");

    /* Set Server */
    response.append("Server: " + request.headers["User-Agent"] + "\r\n");

    /* Set Location */
    if (location.length())
        response.append("Location: " + location + "\r\n");

    /* Set Date */
    char date[100];
    time_t now = time(0);
    strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S GMT", gmtime(&now));
    response.append("Date: " + std::string(date) + "\r\n");

    /* Set Body */
    response.append("\r\n");
}
