#include "../includes/Headers.hpp"

unsigned int fromHexToDec(const std::string &nb) {
    unsigned int x;
    std::stringstream ss;
    ss << nb;
    ss >> std::hex >> x;
    return x;
}

std::string statusCodeString(short statusCode) {
    switch (statusCode) {
        case 100:
            return "Continue";
        case 101:
            return "Switching Protocol";
        case 200:
            return "OK";
        case 201:
            return "Created";
        case 202:
            return "Accepted";
        case 203:
            return "Non-Authoritative Information";
        case 204:
            return "No Content";
        case 205:
            return "Reset Content";
        case 206:
            return "Partial Content";
        case 300:
            return "Multiple Choice";
        case 301:
            return "Moved Permanently";
        case 302:
            return "Moved Temporarily";
        case 303:
            return "See Other";
        case 304:
            return "Not Modified";
        case 307:
            return "Temporary Redirect";
        case 400:
            return "Bad Request";
        case 401:
            return "Unauthorized";
        case 402:
            return "Payment Required";
        case 403:
            return "Forbidden";
        case 404:
            return "Not Found";
        case 405:
            return "Method Not Allowed";
        case 406:
            return "Not Acceptable";
        case 407:
            return "Proxy Authentication Required";
        case 408:
            return "Request Timeout";
        case 409:
            return "Conflict";
        case 410:
            return "Gone";
        case 411:
            return "Length Required";
        case 412:
            return "Precondition Failed";
        case 413:
            return "Request Entity Too Large";
        case 414:
            return "Request-URI Too Long";
        case 415:
            return "Unsupported Media Type";
        case 416:
            return "Requested Range Not Satisfiable";
        case 417:
            return "Expectation Failed";
        case 500:
            return "Internal Server Error";
        case 501:
            return "Not Implemented";
        case 502:
            return "Bad Gateway";
        case 503:
            return "Service Unavailable";
        case 504:
            return "Gateway Timeout";
        case 505:
            return "HTTP Version Not Supported";
        default:
            return "Unknown";
    }
}

int buildHtmlIndex(std::string &dir_name, std::vector<uint8_t> &body, size_t &body_len)
{
    struct dirent   *entityStruct;
    DIR             *directory;
    std::string     dirListPage;

    directory = opendir(dir_name.c_str());
    if (directory == NULL)
    {
        std::cerr << "opendir failed" << std::endl;
        return (1);
    }
    dirListPage.append("<html>\n");
    dirListPage.append("<head>\n");
    dirListPage.append("<title> Index of");
    dirListPage.append(dir_name);
    dirListPage.append("</title>\n");
    dirListPage.append("</head>\n");
    dirListPage.append("<body >\n");
    dirListPage.append("<h1> Index of " + dir_name + "</h1>\n");
    dirListPage.append("<table style=\"width:80%; font-size: 15px\">\n");
    dirListPage.append("<hr>\n");
    dirListPage.append("<th style=\"text-align:left\"> File Name </th>\n");
    dirListPage.append("<th style=\"text-align:left\"> Last Modification  </th>\n");
    dirListPage.append("<th style=\"text-align:left\"> File Size </th>\n");

    struct stat file_stat;
    std::string file_path;

    while((entityStruct = readdir(directory)) != NULL)
    {
        if(strcmp(entityStruct->d_name, ".") == 0)
            continue;
        file_path = dir_name + entityStruct->d_name;
        stat(file_path.c_str() , &file_stat);
        dirListPage.append("<tr>\n");
        dirListPage.append("<td>\n");
        dirListPage.append("<a href=\"");
        dirListPage.append(entityStruct->d_name);
        if (S_ISDIR(file_stat.st_mode))
            dirListPage.append("/");
        dirListPage.append("\">");
        dirListPage.append(entityStruct->d_name);
        if (S_ISDIR(file_stat.st_mode))
            dirListPage.append("/");
        dirListPage.append("</a>\n");
        dirListPage.append("</td>\n");
        dirListPage.append("<td>\n");
        dirListPage.append(ctime(&file_stat.st_mtime));
        dirListPage.append("</td>\n");
        dirListPage.append("<td>\n");
        if (!S_ISDIR(file_stat.st_mode))
            dirListPage.append(to_string(file_stat.st_size));
        dirListPage.append("</td>\n");
        dirListPage.append("</tr>\n");
    }
    dirListPage.append("</table>\n");
    dirListPage.append("<hr>\n");

    dirListPage.append("</body>\n");
    dirListPage.append("</html>\n");

    body.insert(body.begin(), dirListPage.begin(), dirListPage.end());
    body_len = body.size();
    return (0);
}