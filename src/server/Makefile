CC = g++
CFLAGS = -Wall -std=c++11

all: server

server: server.o libserver.so
	$(CC) $(CFLAGS) -o server server.o -L. -lserver

server.o: server.cpp
	$(CC) $(CFLAGS) -c server.cpp

clean:
	rm -f server server.o