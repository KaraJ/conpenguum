CC=g++
CFLAGS=-Wall -ggdb
DFLAGS=$(CFLAGS) -O -c

all: client server

client: testclient.o 
	$(CC) $(CFLAGS) testclient.o -o client -pthread

server: server.o tcpserver.o
	$(CC) $(CFLAGS) server.o tcpserver.o -o server -pthread

clean:
	rm -f *.o *.bak server client

testclient.o: testclient.cpp
	$(CC) $(DFLAGS) testclient.cpp

server.o: server.cpp message.h
	$(CC) $(DFLAGS) server.cpp

tcpserver.o: tcpserver.cpp tcpserver.h
	$(CC) $(DFLAGS) tcpserver.cpp
