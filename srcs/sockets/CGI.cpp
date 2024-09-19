#include "../../includes/sockets/CGI.hpp"

CGI::CGI() {
    this->pid = -1;
    this->exit_status = 0;
    this->av = NULL;
    this->ch_env = NULL;
    this->path = "";
}

CGI::CGI(const CGI &other) {
    this->env = other.env;
    this->ch_env = other.ch_env;
    this->av = other.av;
    this->path = other.path;
    this->pid = other.pid;
    this->exit_status = other.exit_status;
}

CGI &CGI::operator=(const CGI &rhs) {
    if (this != &rhs) {
        this->env = rhs.env;
        this->ch_env = rhs.ch_env;
        this->av = rhs.av;
        this->path = rhs.path;
        this->pid = rhs.pid;
        this->exit_status = rhs.exit_status;
    }
    return (*this);
}

CGI::~CGI() {
    if (this->ch_env) {
        for (int i = 0; this->ch_env[i]; i++)
            free(this->ch_env[i]);
        free(this->ch_env);
    }
    if (this->av) {
        for (int i = 0; this->av[i]; i++)
            free(this->av[i]);
        free(this->av);
    }
    this->env.clear();
}

//void CGI::initEnv(Request &req, const std::vector<LocationBlock>::iterator it_loc) {
//
//}
//
//void CGI::initEnvCGI(Request &req, const std::vector<LocationBlock>::iterator it_loc) {
//
//}
//
//void CGI::execute(short &error_code) {
//
//}
//
//void CGI::clear() {
//
//}
//
//int CGI::findStart(const std::string path, const std::string delim) {
//
//}
//
//std::string CGI::decode(std::string &path) {
//
//}
