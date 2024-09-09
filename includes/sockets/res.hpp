#pragma once

#include "../Headers.hpp"
#include "../../includes/sockets/req.hpp"
#include "../../includes/parsing/ServerBlock2.hpp"
#include "../../includes/Mime.hpp"
//#include "../../includes/sockets/web.hpp"


class Response {
public:
    static Mime mime;
    Response();
    Response(Request &other);
    ~Response();

    ServerBlock server;
    Request request;

    std::string response;
    std::string file;
    std::vector<uint8_t> body;
    size_t body_length;
    std::string response_body;
    std::string location;
    short code;
    char *res;
    bool auto_index;

//    int cgi;
//    Cgi cgi;
//    int cgi_fd[2];
//    size_t cgi_response_length;

    static bool reqError();

    static void LocationMatch(const std::string& path, std::vector<LocationBlock> locations, std::string &key);
    static bool isAllowedMethod(HttpMethod &method, LocationBlock &location, short &code);
    bool handleTarget();
    bool readFile();

    bool buildBody();

    void buildErrorBody();
    void createResponse();
};
