CC = g++
CFLAGS = -Wall -std=c++11

all: server

server: server.o ../lib/libserver.so
	$(CC) $(CFLAGS) -o server server.o -L. -lserver

server.o: server.cpp ../lib/server.h
	$(CC) $(CFLAGS) -c server.cpp server.h

clean:
	rm -f server server.o