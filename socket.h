
/*******************************Blocking send and receive***********************************/

/*Send the number of bytes to be sent. Then send the actual data.*/
void send_full_msg(int socket, void *buffer, int length);

/*First receive the number of bytes to be received. Then receive the actual data to the buffer.*/
int recv_full_msg(int socket, void *buffer, int length);



/***************************Server side*******************************************************/

/*Create a TCP socket, bind and then listen*/
int TCP_server_init(int PORT);

/*Accept a client*/    
int TCP_server_accept_client(int listenfd);

/*Disconnect a connected client*/    
void TCP_server_disconnect_client(int connectfd);

/*Close down the listening socket*/    
void TCP_server_shutdown(int listenfd);



/********************************Client side***************************************************/

/* Connect to a TCP server at PORT at ip*/
int TCP_client_connect(char *ip, int PORT);

/* Disconnect*/
void TCP_client_disconnect(int socketfd);



/************************************Internal Functions*****************************************/

/*Die on error. Print the error and exit if the return value of the previous function is -1*/
void errorCheck(int ret,char *msg);

/*Send length number of bytes from the buffer. This is a blocking call.*/
void send_all(int socket, void *buffer, int length);

/*Receive length number of bytes to the buffer. This is a blocking call. Make sure that buffer is big enough.*/
void recv_all(int socket, void *buffer, int length);