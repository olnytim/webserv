#pragma once

#include "DataStorage.hpp"
#include "SocketListener.hpp"
#include "../parsing/ServerBlock.hpp"

class WebServer : public SocketListener
{
public:
//	WebServer(unsigned short port, const char* ip) :
//			SocketListener(port, ip) {}
    WebServer(const ServerBlock& server)  :
            SocketListener(server.getPort(), server.getListen().c_str(), server.getServerNames()) {
        this->server = server;
    }

protected:
    DataStorage dataStorage;
    ServerBlock server;

	void onClientConnected(int client);
	void onMessageReceived(int client, const char* msg);
	void onClientDisconnected(int client);
};