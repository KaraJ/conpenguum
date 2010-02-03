CC=g++
CFLAGS=-Wall -ggdb
DFLAGS=$(CFLAGS) -O -c

all: client server

client: client.o 
	$(CC) $(CFLAGS) client.o -o client -pthread

server: server.o tcpserver.o
	$(CC) $(CFLAGS) server.o tcpserver.o -o server -pthread

clean:
	rm -f *.o *.bak server client

client.o: client.cpp
	$(CC) $(DFLAGS) client.cpp

server.o: server.cpp
	$(CC) $(DFLAGS) server.cpp

tcpserver.o: tcpserver.cpp tcpserver.h
	$(CC) $(DFLAGS) tcpserver.cpp
