
#include "tunnel.hpp"


int main() {

	SOCKET server;
	SOCKET client;
	SOCKET remote;

	sockaddr_in client_addr;
	int client_len = sizeof(client_addr);

	char ip[INET_ADDRSTRLEN];


	if (!init_api())
		exit(EXIT_FAILURE);


	server = create_socket();
	if (server == INVALID_SOCKET)
		exit(EXIT_FAILURE);


	while (1) {

		client = accept(server, (sockaddr*)&client_addr, &client_len);
		if (client == INVALID_SOCKET)
			continue;

		inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));

		std::cout << "< client connected: " << ip << ": " << ntohs(client_addr.sin_port) << "\n";

		remote = connect_remote();
		if (remote == INVALID_SOCKET) {
			closesocket(client);
			continue;
		}

		tunnel_ctx ctx{ client, remote };
		relay(ctx);

//		closesocket(client);
//		closesocket(remote);
//		std::cout << "< connection closed!\n";
	
	}

	return 0;

}