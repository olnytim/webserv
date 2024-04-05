#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

class SocketListener
{
public:
	bool init();
	bool run();

	SocketListener(unsigned short port, const char* ip) : port(port), ip(ip), sockets(-1), addr_in(), master() {}

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
};