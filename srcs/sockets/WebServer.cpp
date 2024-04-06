#include "../../includes/sockets/WebServer.hpp"
#include <fstream>

void WebServer::onClientConnected(int client) {
    (void)client;
}

void WebServer::onClientDisconnected(int client) {
    (void)client;
}

void WebServer::onMessageReceived(int client, const char* msg) {
    std::istringstream iss(msg);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    std::string content = "<h1>404 not found</h1>";
    std::string fileHtml = "index.html";
    std::string contentType;
    int error_code = 404;

    if (tokens.size() >= 3 && tokens[0] == "GET") {
        fileHtml = "www/" + tokens[1];
    }

    std::ifstream f(fileHtml.c_str());
    if (f.good()) {
        error_code = 200;
        std::stringstream buffer;
        buffer << f.rdbuf();
        content = buffer.str();
    }
    if (fileHtml.find(".html") != std::string::npos) {
        contentType = "text/html";
    } else if (fileHtml.find(".css") != std::string::npos) {
        contentType = "text/css";
    } else if (fileHtml.find(".jpeg") != std::string::npos) {
        contentType = "jpeg";
        std::fstream f(fileHtml.c_str(), std::ios::in | std::ios::binary);
        if (f.good()) {
            f.seekg(0, std::ios::end);
            content.resize(f.tellg());
            f.seekg(0, std::ios::beg);
            f.read(&content[0], content.size());
        }
    }
    f.close();
    std::ostringstream response;
    response << "HTTP/1.1 " << error_code << " OK\r\n"
             << "Cache-Control: no-cache, no-store, must-revalidate\r\n"
             << "Content-Type: " << contentType << "\r\n"
             << "Content-Length: " << content.size() << "\r\n"
             << "Connection: close\r\n"
             << "\r\n"
             << content;
    std::string output = response.str();
    sendToClient(client, output.c_str(), output.length() + 1);
}