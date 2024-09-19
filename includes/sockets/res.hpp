#pragma once

#include "../Headers.hpp"
#include "../../includes/sockets/req.hpp"
#include "../../includes/parsing/ServerBlock.hpp"
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
    bool auto_index;

    int cgi;
//    int cgi_fd[2];
//    CgiRes cgi_res;

    static bool reqError();

    static void LocationMatch(const std::string& path, std::vector<LocationBlock> locations, std::string &key);
    bool isAllowedMethod(LocationBlock &location);
    bool handleTarget();
    bool readFile();

    bool buildBody();

    std::string getErrorPage();
    void setDefaultErrorPages();
    void buildErrorBody();
    void createResponse();
    void clear();
};
