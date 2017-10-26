# socketLibC

**A simple and easy to use TCP Linux socket programming library**

Socket programs written in C are quite fast. However, writing a working socket program in C is timing consuming unless one is very experienced. Further, debugging will consumes hours.
There are three major reasons for this being hard with infinitely longer debugging time.
1. The system calls do not handle errors internally. The programmer is supposed to do error handling. However, coders simply get lazy to write error handling code at the beginning and later waste hours for debugging.
2. The "recv" system call by default does not guarantee to wait until the requested amount of data is fully received. The man page says "The receive calls normally return any data available, up to the requested amount, rather than waiting for receipt of the full amount requested". If someone assumes "recv" is fully blocking without seeing this, it will be hard to find why sometimes data is mysteriously lost. 
3. Even if "recv" is called in a loop, knowing when to end the loop is tricky. That is, the receiver cannot magically know the size of the message to expect. One solution is to send the number of bytes that we are going to send, before sending the message. Now the receiver can wait till this number of bytes are received.

socketLibC is a very simple TCP library written such that all above three challenges are solved. It contains less than 10 functions. 
**See socket.h for functions and help**

Source files are : 

- socket.h contains the Function prototypes.
- socket.c implements the socketLibC function.

- server.c is the example server program.
- client.c is the example client program.



## Installing

Just run the make command

```
git clone https://github.com/hasindu2008/socketLibC.git
cd socketLibC && make
```


## Running

First run the server binary and then the client binary

```
./server
./client 127.0.0.1 
```

