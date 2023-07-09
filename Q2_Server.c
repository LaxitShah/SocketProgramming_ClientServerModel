#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>//it has necessary function to create a socket 
#include<stdlib.h>
#include<netinet/in.h>//required constant and structure needed for internet domain address 
#include<string.h>
#define PORT 8081

int main(int argc,char const *argv[])
{
    int fd , new_socket , val_read ; //fd:file description 
	struct sockaddr_in address;
    char reply[20];
	int opt=1;
	int addrlen=sizeof(address);
	char buffer[1024];
	char *hello="Hello There from Server";
   
    //socket is used for socket creation
    //it tis there in sys/socket.h header file
    //AF_INET means IPV4 and SOCK_STREAM stands for TCP
	if((fd=socket(AF_INET,SOCK_STREAM,0))==0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
    //setsockopt is used to control the behaviour of the socket
    //SOL SOCKET represent the socket level
	if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
    //initializing the structure    
	address.sin_family=AF_INET;//for address
	address.sin_addr.s_addr=INADDR_ANY;//Any Address available 
	address.sin_port=htons(PORT);//convert port to network byte using htons

    //bind is used to assign an socket to a socket() function
    //sockaddr is used to represent information such as port and address can be stored in this structure
    //length of address passed as second parameter 
	if(bind(fd,(struct sockaddr *)&address,sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
    
    //listen function is used to make server node wait 
    // and listen for connections from the client node specified by the bind
    if(listen(fd,3)<0)//maximum 3 connection 
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

    //accept is used to establish the connection between server and client
    //To transfer the Data

    //Address is a variable from the socket returned from the function stored
    //Address Length determines the size of the address
	if((new_socket=accept(fd,(struct sockaddr *)&address,(socklen_t *)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
        //receive data sent by the client
		val_read = read( new_socket , buffer , 1024); //returns the no. of bytes of data that has been read
		
        printf("Client Message: %s\n", buffer );
		memset( buffer , 0 , 1024);//it is used to fill the block with particular value
		
        printf("Message From Server:");
		// %*[^\n] scans everything until a \n, but doesn't scan in the \n. The asterisk(*) tells it to discard whatever was scanned.
        
        //%*c scans a single character, which will be the \n left over by %*[^\n] in this case. The asterisk instructs scanf to discard the scanned character.
		
        scanf("%[^\n]%*c",reply);
        
        //it sends data to the client
        send(new_socket , reply , strlen(reply) , 0 ); 

		printf("---replied---\n");
		memset( reply , 0 , 20);
	}

	return 0;
}