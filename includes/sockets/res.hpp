#pragma once

#include "../Headers.hpp"
#include "../../includes/sockets/req.hpp"
#include "../../includes/parsing/Config.hpp"
#include "../../includes/Mime.hpp"
#include "../../includes/sockets/CGI.hpp"
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
    int cgi_fd[2];
    CGI cgi_resp;

    bool reqError();

    static void LocationMatch(const std::string& path, std::vector<LocationBlock> locations, std::string &key);
    bool isAllowedMethod(LocationBlock &location_temp, HttpMethod &method, short &code_temp);

    bool handleCGI(std::string &key);
    bool handleTarget();
    bool readFile();

    bool buildBody();

    std::string getErrorPage() const;
    std::string readErrorPage(const std::string &filename);
    void setDefaultErrorPages();
    void buildErrorBody();
    void createResponse();
    void clear();
};
