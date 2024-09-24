#pragma once

#include "../Headers.hpp"

enum HttpMethod
{
    GET = 1,
    POST = 2,
    DELETE = 3,
    NONE = 4
};

class Request {
public:
    HttpMethod method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;
    short error_code;

    Request();

    static HttpMethod stringToHttpMethod(const std::string& methodStr);
    bool reqParse(const char* data, size_t size);
    void clear();
};