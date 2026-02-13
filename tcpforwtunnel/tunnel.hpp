
#include "headers.hpp"

/*
	this file contains the main logic of the tunnel and the configuration of the tunnel.
	you can modify the configuration in the config namespace and the main logic in the functions below additionally
	you can test by your own, change the remote server and port to test with your own server, or you can use the provided echo server in the repo for testing
	for ethical and legal reasons, don't use this tunnel for malicious purposes, and don't use it to attack or hack any server without permission, this tunnel is for educational purposes only
	you can add more functions for more advanced features like encryption, compression, etc...
 
 */

namespace config
{

	constexpr int BUFFER_SIZE = 4096;
	constexpr int LOCAL_PORT = 9909;
	constexpr const char* REMOTE_IP = "127.0.0.1";
	//constexpr const char* REMOTE_IP = "13.107.18.254";
	constexpr int REMOTE_PORT = 8080; // 61079
	//constexpr int REMOTE_PORT = 443; // 61079

};

struct addr_config
{
	WSADATA ws;

	SOCKET server_socket;

	sockaddr_in server_addr;

};

struct tunnel_ctx
{

	SOCKET client_socket = INVALID_SOCKET;
	SOCKET remote_socket = INVALID_SOCKET;

};


bool init_api(void);
void relay(tunnel_ctx &ctx);

SOCKET create_socket(void);
SOCKET connect_remote(void);


