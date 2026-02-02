
#include "headers.hpp"

namespace config
{

	constexpr int BUFFER_SIZE = 4096;
	constexpr int LOCAL_PORT = 9909;
	constexpr const char* REMOTE_IP = "127.0.0.1";
	constexpr int REMOTE_PORT = 49667;

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


