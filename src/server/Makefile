CC = g++
CFLAGS = -Wall -std=c++11

all: server

server: server.o libserver.so
	$(CC) $(CFLAGS) -o server server.o -L. -lserver

server.o: server.cpp server.h
	$(CC) $(CFLAGS) -c server.cpp server.h

clean:
	rm -f server server.o