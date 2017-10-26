#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "socket.h"

#define BUFFER_SIZE 1000

int main(){
    
    char buffer[BUFFER_SIZE];
    
    //create a listening socket on port 20000
	int listenfd=TCP_server_init(20000);
    
    //accept a client connection
    int connectfd = TCP_server_accept_client(listenfd);
    
	//get message from client
	int received = recv_full_msg(connectfd,buffer,BUFFER_SIZE);
	
    //print the message
    buffer[received]='\0'; //null character before priniting the stringsince
	fprintf(stderr,"Recieved : %s\n",buffer); 
 
    //Copy a string to buffer
    strcpy(buffer,"Hi! This is the server reply.");
 
    //send a message to the client
    send_full_msg(connectfd,buffer,strlen(buffer));
 
    //close doen the client connection
    TCP_server_disconnect_client(connectfd);
    
    //close the down the listening socket
    TCP_server_shutdown(listenfd);

    return 0;
    
}

