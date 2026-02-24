TCP Tunnel – Event-Driven Relay Proxy in C++

This project implements a TCP Tunnel (Layer 4 relay proxy) in C++ using the Windows Sockets API (Winsock 2.2).
It establishes a bidirectional communication channel between a local client and a remote service, transparently forwarding traffic while allowing real-time payload inspection.


The system was designed as a network protocol study artifact, focusing on:
- TCP connection lifecycle
- Socket multiplexing with select
- Buffer-level traffic inspection
- Controlled relay architecture
- Hex-level payload analysis


Flow Description:
- Tunnel listens on a local port.
- Client establishes TCP connection with the tunnel.
- Tunnel establishes a second TCP connection to the remote service.
- A multiplexed event loop relays traffic in both directions.
- Payload is optionally logged in hexadecimal representation.


This project is relevant for:
- Understanding TCP state transitions
- Studying transparent proxy mechanisms
- Implementing controlled MITM laboratory environments
- Inspecting raw HTTP traffic
- Observing TLS handshake behavior (when paired with SSL tools)
- Experimental traffic analysis


It provides a foundation for:
- TLS interception research
- Protocol fingerprinting
- Deep Packet Inspection (DPI) experimentation
- Traffic manipulation studies
- Intrusion detection prototypes

SETUP:

Remote server:
```
127.0.0.1:8080
```

Tunnel:
```
127.0.0.1:9909
```

Client test:
```
curl http://127.0.0.1:9909
```

Output:
```
47 45 54 20 2F 20 48 54 54 50 2F 31 2E 31 ...
```
Which corresponds to:
GET / HTTP/1.1
you can see in powershell.

BUILD ENVIRONMENT: 
Windows 10+
Visual Studio
C++17
Winsock2
```
ws2_32.lib
```

| Decision                    | Rationale                                          |
| --------------------------- | -------------------------------------------------- |
| select() instead of threads | Deterministic behavior and easier state inspection |
| Hex dump logging            | Protocol-level visibility                          |
| Blocking sockets            | Controlled experimental environment                |
| No external dependencies    | Full low-level understanding                       |


Possible Extensions:
- Non-blocking I/O
- epoll / IOCP adaptation
- TLS wrapping via OpenSSL
- Thread pool model
- Traffic filtering rules
- Rate limiting
- Packet modification engine
- Logging to PCAP format
- Performance benchmarking

Educational Purpose:
- This project was developed as part of ongoing studies in:
- Network protocols
- Socket programming
- TCP/IP internals
- Secure communication systems
- Applied cryptography environments
- It serves as a foundational building block for advanced security research projects.

Information Systems student
Focus: Network Security & Systems Programming
UFSC
