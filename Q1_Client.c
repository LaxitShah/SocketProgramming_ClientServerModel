#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
	int sock = 0, val_read, client_fd;
	struct sockaddr_in serv_addr;
	char* hello = "Hello from client";
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	
    serv_addr.sin_family = AF_INET;//for address
	serv_addr.sin_port = htons(PORT);//convert port to network byte using htons

    //The InetPton function converts an IPv4 or IPv6 Internet network address in its standard text presentation form into its numeric binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<= 0)
    {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}
    //connect function is used to make connection request and connect to the server node
    //returns 0 on successfully connecting the server and -1 for failure

	if ((client_fd= connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr)))< 0)
    {
		printf("\nConnection Failed \n");
		return -1;
	}

    //it sends data to server
	send(sock, hello, strlen(hello), 0);
	printf("Hello message sent\n");

    //receive data sent by the server
	val_read = read(sock, buffer, 1024);
	printf("%s\n", buffer);

	// closing the connected socket
	close(client_fd);
	return 0;
}
