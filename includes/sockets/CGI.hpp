#pragma once

#include "../Headers.hpp"
#include "../parsing/LocationBlock.hpp"
#include "../sockets/req.hpp"

class Request;

class CGI {
public:
    std::map<std::string, std::string> env;
    std::string path;
    pid_t pid;
    int exit_status;
    char **av;
    char **ch_env;

    int pipe_in[2];
    int pipe_out[2];

    CGI();
    CGI(const CGI &other);
    CGI &operator=(const CGI &rhs);
    ~CGI();

    static int findStart(const std::string &path, const std::string &delim);
    std::string getPathInfo(std::string &path, std::vector<std::string> extensions);

    void initEnv(Request &req, std::vector<LocationBlock>::iterator it_loc);
//    void initEnvCGI(Request &req, std::vector<LocationBlock>::iterator it_loc);

    void execute(short &error_code);

//    std::string decode(std::string &path);

    void clear();
};