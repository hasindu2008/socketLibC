CC=gcc
CFLAGS=-Wall

all: server client
	
server : socket.c socket.h server.c
	$(CC) $(CFLAGS) socket.c server.c -o server

client : socket.c socket.h client.c
	$(CC) $(CFLAGS) socket.c client.c -o client

.PHONY: clean

clean:
	rm server client
