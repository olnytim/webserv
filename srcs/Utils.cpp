#include "../includes/Utils.hpp"

int ft_stoi(const std::string &str) {
    int res;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] < '0' || str[i] > '9')
            throw std::invalid_argument("ft_stoi: invalid argument");
    }
    std::stringstream ss(str);
    ss >> res;
    return res;
}

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
            return "Unknown Status Code";
    }
}

std::string getErrorPage(short statusCode) {
    return ("<html>\r\n<head><title>" + toString(statusCode) + " " +
            statusCodeString(statusCode) + " </title></head>\r\n<body>\r\n<center><h1>" +
            toString(statusCode) + " " + statusCodeString(statusCode) + "</h1></center>\r\n");
}

int buildHtmlIndex(std::string &html, std::vector<uint8_t> &data, size_t &size) {
    std::string header = "<html>\r\n<head><title>Index of /</title></head>\r\n<body>\r\n<h1>Index of /</h1>\r\n";
    std::string footer = "</body>\r\n</html>\r\n";
    std::string content;
    std::string link;
    std::string type;
    std::string sizeStr;
    std::string date;
    std::string line;
    std::string path;
    std::string tmp;
    struct stat st;
    struct tm *timeinfo;
    char buffer[80];
    size_t i = 0;

    html = header;
    while (i < size) {
        path = "";
        while (data[i] != '\n') {
            path += data[i];
            i++;
        }
        i++;
        if (path == ".")
            continue;
        if (stat(path.c_str(), &st) == -1) {
            perror("stat");
            return -1;
        }
        timeinfo = localtime(&st.st_mtime);
        strftime(buffer, 80, "%Y-%m-%d %H:%M", timeinfo);
        date = buffer;
        if (S_ISDIR(st.st_mode)) {
            link = "<a href=\"" + path + "/\">" + path + "/</a>";
            type = "Directory";
            sizeStr = "-";
        } else {
            link = "<a href=\"" + path + "\">" + path + "</a>";
            type = "File";
            sizeStr = toString(st.st_size);
        }
        line = "<a href=\"" + path + "\">" + path + "</a> " + sizeStr + " " + date + "\r\n";
        content += line;
    }
    html += content;
    html += footer;
    return 0;
}