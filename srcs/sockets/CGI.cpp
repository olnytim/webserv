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

void CGI::initEnv(Request &req, const std::vector<LocationBlock>::iterator it_loc) {
    std::string ext = path.substr(path.find('.'));
    std::map<std::string, std::string>::iterator it_path = it_loc->ext_path.find(ext);
    if (it_path == it_loc->ext_path.end()) {
        std::cerr << "Error: extension not found" << std::endl;
        return;
    }
    std::string ext_path = it_loc->ext_path[ext];

    this->env["AUTH_TYPE"] = "Basic";
    this->env["CONTENT_LENGTH"] = req.headers["Content-Length"];
    this->env["CONTENT_TYPE"] = req.headers["Content-Type"];
    this->env["GATEWAY_INTERFACE"] = "CGI/1.1";
    int pos = findStart(this->path, "cgi/");
    printf("path: %s\n", this->path.c_str());
    printf("pos: %d\n", pos);
}

//void CGI::initEnvCGI(Request &req, const std::vector<LocationBlock>::iterator it_loc) {
//
//}
//
//void CGI::execute(short &error_code) {
//
//}
//
int CGI::findStart(const std::string &path, const std::string &delim) {
    if (path.empty() || delim.empty())
        return -1;
    size_t pos = path.find(delim);
    if (pos != std::string::npos)
        return pos;
    return -1;
}
//
//std::string CGI::decode(std::string &path) {
//
//}
//
void CGI::clear() {
    this->pid = -1;
    this->exit_status = 0;
    this->path = "";
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
