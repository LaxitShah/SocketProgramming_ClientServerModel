#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
int main(int argc, char const* argv[])
{
	int server_fd, ns, val_read;//ns stands for new socket
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	char* hello = "Hello There from server";

	
	//socket is used for socket creation
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}	

    //setsockopt is used to control the behaviour of the socket
	if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt))) 
    {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	//bind is used to assign an address   to a socket() function
    //sockaddr is used to represent information such as port and address can be stored in this structure
    //length of address passed as second parameter 
	if (bind(server_fd, (struct sockaddr*)&address,sizeof(address))< 0) 
    {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	//listen function is used to make server node wait 
    // and listen for connections from the client node specified by the bind
    if (listen(server_fd, 3) < 0)
    {
		perror("listen");
		exit(EXIT_FAILURE);
	}

     //accept is used to establish the connection between server and client
    //To transfer the Data
	if ((ns= accept(server_fd, (struct sockaddr*)&address,(socklen_t*)&addrlen))< 0)
    {
		perror("accept");
		exit(EXIT_FAILURE);
	}

    //receive data sent by client
	val_read = read(ns, buffer, 1024);
	printf("%s\n", buffer);
    //it send data to client
	send(ns, hello, strlen(hello), 0);
	printf("Hello message sent\n");

	// closing the connected socket
	close(ns);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}
