TCP Tunnel – Event-Driven Relay Proxy in C++

This project implements a TCP Tunnel (Layer 4 relay proxy) in C++ using the Windows Sockets API (Winsock 2.2).
It establishes a bidirectional communication channel between a local client and a remote service, transparently forwarding traffic while allowing real-time payload inspection.

The system was designed as a network protocol study artifact, focusing on:
- TCP connection lifecycle
- Socket multiplexing with select
- Buffer-level traffic inspection
- Controlled relay architecture
- Hex-level payload analysis

+-----------+       +----------------+       +------------------+
|   Client  | <---> | Tunnel Server  | <---> | Remote Service   |
|           |       |  (TCP Relay)   |       | 127.0.0.1:8080   |
+-----------+       +----------------+       +------------------+

Flow Description:
-Tunnel listens on a local port.
-Client establishes TCP connection with the tunnel.
-Tunnel establishes a second TCP connection to the remote service.
-A multiplexed event loop relays traffic in both directions.
-Payload is optionally logged in hexadecimal representation.
