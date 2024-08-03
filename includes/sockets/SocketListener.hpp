#pragma once

#include "../Headers.hpp"

class SocketListener
{
public:
	bool init();
	bool run();

	SocketListener(unsigned short port, const char* ip, const std::vector<std::string> &server_name) :
            port(port), ip(ip), sockets(-1), addr_in(), master(),  server_name(server_name){}

protected:
	virtual void onClientConnected(int client) = 0;
    virtual void onClientDisconnected(int client) = 0;
    virtual void onMessageReceived(int client, const char* msg) = 0;

	static void sendToClient(int client, const char* msg, int length);

private:
	unsigned short  port;
	const char      *ip;
	int             sockets;
	sockaddr_in     addr_in;
	fd_set          master;
    std::vector<std::string> server_name;
};