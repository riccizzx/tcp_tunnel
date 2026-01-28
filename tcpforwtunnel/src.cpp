
#include "tunnel.hpp"

addr_config cfg;
using namespace config;

bool init_api() {

	if (WSAStartup(MAKEWORD(2, 2), &cfg.ws) != 0) {

		std::cerr << "can't initialize winsock api\n";
		return false;

	}

	return true;

}

SOCKET create_socket() {

	cfg.server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (cfg.server_socket == INVALID_SOCKET) {

		std::cerr << "< can't config server socket! <error>\n";
		return INVALID_SOCKET;
	
	}


	int opt = 1;

	setsockopt(cfg.server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));


	cfg.server_addr.sin_family = AF_INET;
	cfg.server_addr.sin_port = htons(LOCAL_PORT);
	cfg.server_addr.sin_addr.s_addr = INADDR_ANY;


	if (bind(cfg.server_socket, (sockaddr*)&cfg.server_addr, sizeof(cfg.server_addr)) == SOCKET_ERROR)
	{
	
		std::cerr << "< err> bind failed!\n";
		closesocket(cfg.server_socket);
		return INVALID_SOCKET;
		
	};


	if (listen(cfg.server_socket, SOMAXCONN) == SOCKET_ERROR)
	{

		std::cerr << "< err> can't put socket in listening state...\n";
		closesocket(cfg.server_socket);
		return INVALID_SOCKET;

	}
	

	std::cout << "< server listening on port: " << LOCAL_PORT << "\n";

	return cfg.server_socket;

}

SOCKET connect_remote() {

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET) {

		std::cerr << "error in initialize socket config\n";
		exit(EXIT_FAILURE);
	
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(REMOTE_PORT);

	inet_pton(AF_INET, REMOTE_IP, &addr.sin_addr);

	if (connect(s, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {

		std::cout << "error in connect remote to the server \n";
		closesocket(s);
		exit(EXIT_FAILURE);

	}

	std::cout << "< connected to remote: " << REMOTE_IP << REMOTE_PORT << "\n";

	return s;

}

void relay(tunnel_ctx& ctx) {

	fd_set readfds;
	char buffer[BUFFER_SIZE];

	while (true)
	{
		FD_ZERO(&readfds);
		FD_SET(ctx.client_socket, &readfds);
		FD_SET(ctx.remote_socket, &readfds);
	
		int maxfd = (ctx.client_socket > ctx.remote_socket ? ctx.client_socket : ctx.remote_socket) + 1;
		
		int ret = select(maxfd, &readfds, nullptr, nullptr, nullptr);
		if (ret <= 0)
			break;

		if (FD_ISSET(ctx.client_socket, &readfds)) {

			int bytes = recv(ctx.client_socket, buffer, sizeof(buffer), 0);
			if (bytes <= 0) break;
			send(ctx.remote_socket, buffer, sizeof(buffer), 0);
		
		}

		if (FD_ISSET(ctx.remote_socket, &readfds)) {

			int bytes = recv(ctx.remote_socket, buffer, sizeof(buffer), 0);
			if (bytes <= 0)break;
			send(ctx.client_socket, buffer, sizeof(buffer), 0);

		}
	
	}

}