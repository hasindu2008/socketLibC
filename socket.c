#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket.h"


/*******************************Blocking send and receive***********************************/

/*Send the number of bytes to be sent. Then send the actual data.*/
void send_full_msg(int socket, void *buffer, int length)
{
    send_all(socket, &length, sizeof(int));
    send_all(socket, buffer, length);
    
}

/*First receive the number of bytes to be received. Then receive the actual data to the buffer. */
int recv_full_msg(int socket, void *buffer, int length)
{
    int expected_length = 0;
    recv_all(socket, &expected_length, sizeof(int));
        
    fprintf(stderr, "receiving a message of size %d\n",expected_length);
    
    if(expected_length>=length){
        fprintf(stderr, "Buffer is too small to fit expected data\n");
    }
    
    recv_all(socket,buffer,expected_length);
    return expected_length;
 
}

/***************************Server side*******************************************************/


/*Create a TCP socket, bind and then listen*/
int TCP_server_init(int PORT){
    
	//initialize variables
	int listenfd,ret;
	struct sockaddr_in server;
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);
	
	//open socket bind and listen
	listenfd = socket(AF_INET,SOCK_STREAM,0); 
	errorCheck(listenfd,"Cannot create socket");
	ret=bind(listenfd,(struct sockaddr *)&server, sizeof(server));
	errorCheck(ret,"Cannot bind");
	fprintf(stderr,"Binding successfull... port : %d\n",PORT);
	ret=listen(listenfd,5);
	errorCheck(ret,"Cannot listen");
	fprintf(stderr,"Listening to port %d...\n",PORT);    
    
    return listenfd;

}

/*Accept a client*/    
int TCP_server_accept_client(int listenfd){

    int connectfd;
    
    struct sockaddr_in client;
	socklen_t clientlen = sizeof(client);
    
	//accept connections
	connectfd = accept(listenfd,(struct sockaddr *)&client, &clientlen);
	errorCheck(connectfd,"Cannot accept");
    
    //get ip to string
    char ip[12];
    inet_ntop(AF_INET, &client.sin_addr,ip, clientlen);
    fprintf(stderr,"Client %s:%d connected\n",ip,client.sin_port);  
    
    return connectfd;

}    
    
/*Disconnect a connected client*/    
void TCP_server_disconnect_client(int connectfd){
	//close sockets 
	int ret=close(connectfd);
	errorCheck(ret,"Cannot close socket");
	fprintf(stderr,"Client disconnected\n");
}    
    
/*Close down the listening socket*/    
void TCP_server_shutdown(int listenfd){
    //we do not need the listening socket now
    int ret=close(listenfd);
    errorCheck(ret,"Cannot close socket");
}    
    
    
/********************************Client side***************************************************/


/* Connect to a TCP server at PORT at ip*/
int TCP_client_connect(char *ip, int PORT){
	
    //socket for connecting
	int socketfd = socket(AF_INET,SOCK_STREAM,0);
    errorCheck(socketfd,"Cannot create socket");
	
	//initializing the server address and assigning port numbers
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_port = htons(PORT);
	
	//connecting
	int ret=connect(socketfd,(struct sockaddr *)&server, sizeof(server));
    errorCheck(ret,"Cannot connect");    
    fprintf(stderr,"Connected to server \n");
    
    return socketfd;
    
}


/* Disconnect*/
void TCP_client_disconnect(int socketfd){
    
	//closing sockets
	int ret = shutdown(socketfd,SHUT_RDWR);   
    errorCheck(ret,"Cannot disconnect");    
 	ret = close(socketfd);   
    errorCheck(ret,"Cannot close socket");     
}




/************************************Internal Functions*****************************************/

/*Die on error. Print the error and exit if the return value of the previous function is -1*/
void errorCheck(int ret,char *msg){
	if(ret==-1){
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

/*Send length number of bytes from the buffer. This is a blocking call.*/
void send_all(int socket, void *buffer, int length)
{
    char *ptr = (char*) buffer;
    int i=0;
    while (length > 0)
    {
        i = send(socket, ptr, length, 0);
        if (i < 1){
            perror("Could not send all data");
        }
        ptr += i;
        length -= i;
    }
    return;
}

/*Receive length number of bytes to the buffer. This is a blocking call. Make sure that buffer is big enough.*/
void recv_all(int socket, void *buffer, int length)
{
    char *ptr = (char*) buffer;
    int i=0;
    while (length > 0)
    {
        i = recv(socket, ptr, length, 0);
        if (i < 1){
            perror("Could not receive all data");
        }
        ptr += i;
        length -= i;
    }
    return;
}
    