#include "../../includes/sockets/SocketListener.hpp"

bool SocketListener::init() {
	sockets = socket(AF_INET, SOCK_STREAM, 0);
	if (sockets == -1)
		return false;

	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(port);
	inet_pton(AF_INET, ip, &addr_in.sin_addr);
	if (bind(sockets, (struct sockaddr*)&addr_in, sizeof(addr_in)) == -1)
		return false;

	if (listen(sockets, SOMAXCONN) == -1)
		return false;

	FD_ZERO(&master);
	FD_SET(sockets, &master);

	return true;
}

bool SocketListener::run() {
	while (true) {
		fd_set copy = master;
		int max_fd = -1;
		for (int fd = 0; fd < FD_SETSIZE; ++fd) {
			if (FD_ISSET(fd, &copy) && fd > max_fd)
				max_fd = fd;
		}
		max_fd += 1;

		int socketCount = select(0, &copy, NULL, NULL, NULL);
		if (socketCount == -1)
			continue;

		for (int sock = 0; sock < max_fd; ++sock)
		{
			if (FD_ISSET(sock, &copy)) {
				if (sock == sockets) {
					int client = accept(sockets, NULL, NULL);
					if (client == -1)
						continue;

					FD_SET(client, &master);
					onClientConnected(client);
				}
				else {
					char buf[4096];
					std::memset(buf, 0, sizeof(buf));

					int bytesIn = recv(sock, buf, 4096, 0);
					if (bytesIn <= 0) {
						onClientDisconnected(sock);
						close(sock);
						FD_CLR(sock, &master);
					}
					else
						onMessageReceived(sock, buf, bytesIn);
				}
			}
		}
	}
}

// send and broadcast messages
void SocketListener::sendToClient(int client, const char* msg, int length) {
	send(client, msg, length, 0);
}

void SocketListener::broadcastToClients(int sendingClient, const char* msg, int length) {
//    for (int i = 0; i < master.fd_count; i++) {
//        int outSock = master.fd_array[i];
//        if (outSock != sockets && outSock != sendingClient)
//            sendToClient(outSock, msg, length);
//    }
	(void)sendingClient;
	(void)msg;
	(void)length;
}
