#pragma once

#include "SocketListener.hpp"
#include "../parsing/ServerBlock.hpp"

class WebServer : public SocketListener
{
public:
	WebServer(unsigned short port, const char* ip) :
			SocketListener(port, ip) {}
    WebServer(ServerBlock server)  :
            SocketListener(server.getPort(), server.getListen().c_str()) {
        this->server = server;
    }

protected:
    ServerBlock server;

	void onClientConnected(int client);
	void onMessageReceived(int client, const char* msg);
	void onClientDisconnected(int client);
};