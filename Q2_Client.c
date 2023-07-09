#include <stdio.h> 
#include <sys/socket.h>//it has necessary function to create a socket 
#include <arpa/inet.h> //it contains defination for internet operation
#include <unistd.h> 
#include <string.h> 
#define PORT 8081

int main(int argc, char const *argv[]) {

    int sock = 0, val_read ;
    struct sockaddr_in serv_addr ;
    char *exit_msg = "exit";
    char msg[20];
    char buffer[1024] = {0};
    //socket is used for socket creation
    //it tis there in sys/socket.h header file
    //AF_INET means IPV4 and SOCK_STREAM stands for TCP
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1; 
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);


    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n"); 
        return -1;
    }
    //connect function is used to make connection request and connect to the server node
    //returns 0 on successfully connecting the server and -1 for failure
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf ("\n Connection Failed \n");
        return -1;
    }
    while (1) {
        
        printf("Message From Client: \n");
	    scanf("%[^\n]%*c", msg);
	    
        if (!strcmp(msg, exit_msg))
        {
		    close (sock);//it is used to terminate the connection
		    return 0;
    	}
	    
        send(sock , msg , strlen(msg) , 0); 
	    val_read = read( sock , buffer , 1024);//returns the no. of byte the data that has been used
	    printf("Server Message:%s\n",buffer);
	    memset( buffer , 0 , 1024);
	    memset( msg , 0 , 20); 
        printf("\n----\n");
    }		
    return 0;
}