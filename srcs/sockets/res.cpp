#include "../../includes/sockets/res.hpp"

void Response::sendResponse(const int &fd, const char *msg) {
    (void)fd;
    (void)msg;
//    std::istringstream iss(msg);
//    std::vector<std::string> tokens;
//    std::string token;
//    while (std::getline(iss, token, ' ')) {
//        tokens.push_back(token);
//    }
//
////    for (size_t i = 0; i < tokens.size(); i++) {
////        std::cout << "Token " << i << ": " << tokens[i] << std::endl;
////    }
//    std::string fileHtml = "www/index.html";
//    std::string content = "<h1>404 not found</h1>";
//    fileHtml = "www/index.html";
//    std::string contentType;
//    int error_code = 404;
//
//    if (tokens.size() >= 3 && tokens[0] == "GET") {
//        fileHtml = "www/" + tokens[1];
//    }
//
//    std::ifstream f(fileHtml.c_str());
//    if (f.good()) {
//        error_code = 200;
//        std::stringstream buffer;
//        buffer << f.rdbuf();
//        content = buffer.str();
//    }
//    if (fileHtml.find(".html") != std::string::npos) {
//        contentType = "html";
//    } else if (fileHtml.find(".css") != std::string::npos) {
//        contentType = "css";
//    } else if (fileHtml.find(".jpeg") != std::string::npos) {
//        contentType = "jpeg";
//    }
//    f.close();
//    std::ostringstream response;
//    response << "HTTP/1.1 " << error_code << " OK\r\n"
//             << "Cache-Control: no-cache, no-store, must-revalidate\r\n"
//             << "Content-Type: text/html" << "\r\n"
//             << "Content-Length: " << content.size() << "\r\n"
//             << "Connection: close\r\n"
//             << "\r\n"
//             << content;
//    std::string output = response.str();
//    send(fd, output.c_str(), output.length() + 1, 0);
}