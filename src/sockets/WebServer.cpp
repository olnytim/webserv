#include "../../includes/sockets/WebServer.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

void WebServer::onClientConnected(int client) {
	(void)client;
}

void WebServer::onClientDisconnected(int client) {
	(void)client;
}

void WebServer::onMessageReceived(int client, const char* msg, int length) {
	(void)length;
	std::istringstream iss(msg);
	std::vector<std::string> tokens;
	std::string token;
	while (std::getline(iss, token, ' ')) {
		tokens.push_back(token);
	}

	std::string content = "<h1>404 not found</h1>";
	std::string fileHtml = "index.html";
	int error_code = 404;

	if (tokens.size() >= 3 && tokens[0] == "GET") {
		fileHtml = "../www/" + tokens[1];
	}

	std::ifstream f(fileHtml.c_str());
	if (f.good()) {
		error_code = 200;
		std::stringstream buffer;
		buffer << f.rdbuf();
		content = buffer.str();
	}
	f.close();
	std::ostringstream response;
	std::cout << content.size() << std::endl;
	response << "HTTP/1.1 " << error_code << " OK\r\n"
			 << "Cache-Control: no-cache, no-store, must-revalidate\r\n"
			 << "Content-Type: text/html\r\n"
			 << "Content-Length: " << content.size() << "\r\n"
			 << "Connection: close\r\n"
			 << "\r\n"
			 << content;
	std::string output = response.str();
	sendToClient(client, output.c_str(), output.length() + 1);
}
