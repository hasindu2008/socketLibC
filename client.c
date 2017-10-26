#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "socket.h"

#define BUFF_SIZE 1000


int main(int argc, char *argv[]){
	
	//argument check check
	if(argc != 2){
		fprintf(stderr, "Not enough args. Usage  %s <ip_address>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
    
    char buffer[BUFF_SIZE]="Hi! I am the client. Serve me please!";
	
    //Connect to the server given as argument on port 20000
    int socketfd = TCP_client_connect(argv[1], 20000);
	
    //send the message
    send_full_msg(socketfd, buffer, strlen(buffer));

    //receive the message
	int received = recv_full_msg(socketfd,buffer,BUFF_SIZE);
    
    //print the message
	buffer[received]='\0';  //null character before priniting the string
	fprintf(stderr,"Recieved : %s\n",buffer);
	
    //close the connection
	TCP_client_disconnect(socketfd);

	
	return 0;
}


