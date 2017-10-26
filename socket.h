
/******************************* Blocking Send and Receive Functions***********************************/

/*  Function to send data

    arguments : socket - socket to which the data is to be sent
                buffer - address of the buffer containing the data to be sent (This can be any pointer casted to void*)
                length - size of the data to be sent (in bytes) 

    This function is a blocking call. It returns only when a 'length' number of bytes have been successfully sent.
    Error checking is handling inside. 
    Internally. This function first sends the number of bytes that is going to be sent. Then only, it sends the actual data.
    It will keep trying in a loop until all data is pushed. As the number of bytes is sent to the receiver first,
    receiver will be able wait until all data is received.
    
*/
void send_full_msg(int socket, void *buffer, long length);


/*  Function to receive data 

    arguments : socket - socket to which the data is to be received
                buffer - address of the buffer to put in the receiving data
                length - the maximum size of the buffer (in bytes) 
    return value : the number of bytes received            

    This function is a blocking call. It returns only when a message sent through "send_full_msg" is fully received. 
    This is possible only because "send_full_msg" first send the number of bytes to be sent. This function sits in a loop until 
    the expected number of bytes is fully received. The it returns the number of received bytes
    Don't confuse this with the argument "length". Argument "length" is the max size of the buffer,
    which is needed inside the function to prevent any overflows. 
    
*/
long recv_full_msg(int socket, void *buffer, long length);



/***************************Server side*******************************************************/

/*Create a TCP socket on PORT
  Internally it performs binding and listening system calls
  Returns the listening socket
  */
int TCP_server_init(int PORT);

/*Accept a client through the listening socket "listenfd"
  Return the connection socket.  
*/    
int TCP_server_accept_client(int listenfd);

/*Disconnect a connected client*/    
void TCP_server_disconnect_client(int connectfd);

/*Close down the listening socket*/    
void TCP_server_shutdown(int listenfd);



/********************************Client side***************************************************/

/* Connect to a TCP server at the port "PORT" at IP address "ip"
   returns the connection socket
*/
int TCP_client_connect(char *ip, int PORT);

/* Disconnect*/
void TCP_client_disconnect(int socketfd);






