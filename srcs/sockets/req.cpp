#include "../../includes/sockets/req.hpp"

HttpMethod Request::stringToHttpMethod(const std::string& methodStr) {
    if (methodStr == "GET") return GET;
    if (methodStr == "POST") return POST;
    if (methodStr == "PUT") return PUT;
    if (methodStr == "DELETE") return DELETE;
    return NONE;
}

void Request::reqParse(const char* data, size_t size) {
    std::istringstream stream(std::string(data, size));
    std::string line;

    // Parse request line
    if (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        std::string methodString;
        lineStream >> methodString >> path >> version;

        method = stringToHttpMethod(methodString);
        if (method == NONE) {
            std::cerr << "Invalid request method\n";
            return;
        }

        if (path.empty() || version.empty()) {
            std::cerr << "Invalid request line\n";
            return;
        }
    }
    else {
        std::cerr << "Invalid request data\n";
        return;
    }

    // Parse headers
    while (std::getline(stream, line) && line != "\r") {
        std::string key, value;
        std::istringstream headerStream(line);
        if (std::getline(headerStream, key, ':') && std::getline(headerStream, value)) {
            headers[key] = value;
            printf("Header: %s: %s\n", key.c_str(), value.c_str());
        }
    }

    // Parse body (if any)
    if (stream) {
        std::istreambuf_iterator<char> begin(stream);
        std::istreambuf_iterator<char> end;
        body.assign(begin, end);
    }
}