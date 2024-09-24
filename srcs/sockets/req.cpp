#include "../../includes/sockets/req.hpp"

Request::Request() : method(NONE) {
    error_code = 0;
}

HttpMethod Request::stringToHttpMethod(const std::string& methodStr) {
    if (methodStr == "GET") return GET;
    if (methodStr == "POST") return POST;
    if (methodStr == "PUT") return PUT;
    if (methodStr == "DELETE") return DELETE;
    return NONE;
}

bool Request::reqParse(const char* data, size_t size) {
    std::istringstream stream(std::string(data, size));
    std::string line;

    if (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        std::string methodString;
        lineStream >> methodString >> path >> version;

        method = stringToHttpMethod(methodString);
        if (method == NONE) {
            return false;
        }

        if (path.empty() || version.empty()) {
            return false;
        }
    }
    else {
        return false;
    }
    while (std::getline(stream, line) && line != "\r") {
        std::string key, value;
        std::istringstream headerStream(line);
        if (std::getline(headerStream, key, ':') && std::getline(headerStream, value))
            headers[key] = value;
    }
    if (stream) {
        std::istreambuf_iterator<char> begin(stream);
        std::istreambuf_iterator<char> end;
        body.assign(begin, end);
    }
    return true;
}

void Request::clear() {
    method = NONE;
    path.clear();
    version.clear();
    headers.clear();
    body.clear();
}
