# SocketProgramming_ClientServerModel

Socket programming is a way of connecting two nodes on a network to commu-
nicate with each other. Server forms the listener socket while the client reaches
out to the server.For the TCP and UDP connection, socket binding process
works differently. In computer networking, an Internet socket or network socket
is an endpoint of a bidirectional inter process communication flow across an
internet protocol based computer network such as the internet.
A socket is a communications connection point (endpoint) that you can name
and address in a network. Socket programming shows how to use socket APIs
to establish communication links between remote and local processes.
The processes that use a socket can reside on the same system or different
systems on different networks. Sockets are useful for both stand-alone and net-
work applications. Sockets allow you to exchange information between processes
on the same machine or across a network, distribute work to the most efficient
machine, and they easily allow access to centralized data. Socket application
program interfaces (APIs) are the network standard for TCP/IP shown in fig 1.
Here is the tutorial link for better understanding of socket and programming:
https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html


# Client-Server model

Stages for server

1. Socket creation: By using the below function, you are able to make
the socket.
int sockfd = socket(domain, type, protocol);
2. Socket Binding: This function helps to assign a unique address to the
socket.
int bind(int sockfd, const struct sockaddr ∗addr, socklen t addrlen);
3. Listen: In this mode socket is ready to accept the client. In this mode
the client approaches the server to make a connection.

 4. Accept: Extract the first connection from the listening queue.Create new
connected socket and return new file descriptor to the referred socket.
int new socket = accept(int sockfd, struct sockaddr ∗addr, socklen t ∗addrlen);

Stages for client

1. Connect: Helps to connect the specific socket to establish connection.
int connect(int sockfd, const struct sockaddr ∗addr, socklen t addrlen);

# How To Run

1. Open a terminal
2. Type “gcc server.c -o server”, and press enter.
3. Type “./server”, and press enter.
4. Open 2nd terminal
5. Type “gcc client.c -o client”, and press enter.
6. Type “./client”, and press enter.
7. Both the server and client are running simultaneously.
8. Note: Always run the server first.

# TCP Client Server Model

Two types of internet sockets:
1. Stream sockets: They are connection oriented reliable sockets also called
TCP sockets.
2. Datagram sockets: They are connectionless unreliable sockets also called
UDP sockets
Most inter-process communication across the network uses the client server
model. These terms refer to the two processes which will be communicating
with each other. One of the two processes, the client, connects to the other
process, the server, typically to make a request for information. Notice that the
client needs to know of the existence of and the address of the server, but the
server does not need to know the address of (or even the existence of) the client
prior to the connection being established.
Notice also that once a connection is established, both sides can send and
receive information. The system calls for establishing a connection are somewhat
different for the client and the server, but both involve the basic construct of
a socket. A socket is one end of an inter-process communication channel.
