# Client-Server


This is a C program that implements a simple user-server interface that can handle commands sent by clients. The program listens for incoming connections on a specific port and accepts client connections. After the connection is established, the server waits for the commands sent by the client, executes them and sends back the results.

##server.c
In the main() function, the program creates a socket, binds it to a port, and listens for incoming connections. When a client connects, the server sends a "ready" message and waits for the client to send a command. The program then reads the command from the client, parses it using command_handler(), and executes the appropriate action. The server keeps track of the commands executed by the client in an array called history, and sends the appropriate response back to the client.
The program defines an enum type Command that represents the possible commands that the server can handle. These commands include CONNECT, DISCONNECT, LS, HISTORY, TIME, HOST, and NOT. The function command_handler takes a command string and returns the appropriate Command value.



#client.c
this program establishes a TCP connection to a server running on localhost on port 25525 and sends messages to it. The program first creates a socket using the Socket() function, then specifies the address of the server it wants to connect to using the sockaddr_in struct. It then connects to the server using the Connect() function.

After establishing the connection, the program sends the string "start\n" to the server using the write() function.

#errorproc.h
This header file contains function declarations for Socket(), Bind(), Listen(), Accept(), Connect(), and Inet_pton().

The Socket() function creates a new socket of a specified domain, type, and protocol, and returns a socket descriptor that can be used for further socket operations.

The Bind() function assigns a local address to a socket identified by its descriptor sockfd.

The Listen() function marks the socket referred to by sockfd as a passive socket, that is, a socket that will be used to accept incoming connection requests using the Accept() function.

The Accept() function accepts a new connection on a socket, and returns a new socket descriptor that can be used to communicate with the newly connected client.

The Connect() function is used by a client to establish a connection to a server identified by the address and port number specified in addr.

The Inet_pton() function converts a string containing an IPv4 or IPv6 address to a binary representation that can be used by network programs.

# errorproc.c
errorproc.c file implements these functions, which print an error message to stderr and exit the program if a socket operation fails.


