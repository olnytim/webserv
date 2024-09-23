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

int CGI::findStart(const std::string &path, const std::string &delim) {
    if (path.empty() || delim.empty())
        return -1;
    size_t pos = path.find(delim);
    if (pos != std::string::npos)
        return pos;
    return -1;
}

std::string CGI::getPathInfo(std::string &path, std::vector<std::string> extensions) {
    std::string tmp;
    size_t start, end;

    for (std::vector<std::string>::iterator it_ext = extensions.begin(); it_ext != extensions.end(); ++it_ext) {
        start = path.find(*it_ext);
        if (start != std::string::npos)
            break;
    }
    if (start == std::string::npos)
        return "";
    if (start + 3 >= path.size())
        return "";
    tmp = path.substr(start + 3, path.size());
    if (!tmp[0] || tmp[0] != '/')
        return "";
    end = tmp.find("?");
    return (end == std::string::npos ? tmp : tmp.substr(0, end));
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
    this->env["SCRIPT_NAME"] = this->path;
    this->env["SCRIPT_FILENAME"] = ((pos < 0 || (size_t)(pos + 4) > this->path.length()) ? "" : this->path.substr(pos + 4, this->path.length()));
    this->env["PATH_INFO"] = getPathInfo(req.path, it_loc->getCgiExt());
    this->env["REMOTE_ADDR"] = req.headers["Host"];
    pos = findStart(req.headers["Host"], ":");
    this->env["SERVER_NAME"] = (pos > 0 ? req.headers["Host"].substr(0, pos) : "");
    this->env["SERVER_PORT"] = (pos > 0 ? req.headers["Host"].substr(pos + 1, req.headers["Host"].length()) : "");
    this->env["REQUEST_METHOD"] = req.method;
    this->env["SERVER_COOKIE"] = req.headers["Cookie"];
    this->env["DOCUMENT_ROOT"] = it_loc->getRoot();
    this->env["REQUEST_URI"] = req.path;
    this->env["SERVER_PROTOCOL"] = "HTTP/1.1";
    this->env["REDIRECT_STATUS"] = "200";
    this->env["SERVER_SOFTWARE"] = "webserv";

    this->ch_env = (char **)calloc(sizeof(char *), this->env.size() + 1);
    std::map<std::string, std::string>::const_iterator it = this->env.begin();
    for (int i = 0; it != this->env.end(); it++, i++) {
        std::string tmp = it->first + "=" + it->second;
        this->ch_env[i] = strdup(tmp.c_str());
    }
    this->av = (char **)malloc(sizeof(char *) * 3);
    this->av[0] = strdup(ext_path.c_str());
    this->av[1] = strdup(this->path.c_str());
    this->av[2] = NULL;
}

void CGI::execute(short &error_code) {
    if (this->av[0] == NULL || this->av[1] == NULL) {
        error_code = 500;
        return;
    }
    if (pipe(pipe_in) < 0) {
        error_code = 500;
        return;
    }
    if (pipe(pipe_out) < 0) {
        close(pipe_in[0]);
        close(pipe_in[1]);
        error_code = 500;
        return;
    }
    this->pid = fork();
    if (this->pid == 0) {
        dup2(pipe_in[0], STDIN_FILENO);
        dup2(pipe_out[1], STDOUT_FILENO);
        close(pipe_in[0]);
        close(pipe_in[1]);
        close(pipe_out[0]);
        close(pipe_out[1]);
        this->exit_status = execve(this->av[0], this->av, this->ch_env);
        exit(this->exit_status);
    }
    else if (this->pid > 0) {}
    else
        error_code = 500;
}

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
