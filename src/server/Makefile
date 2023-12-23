CC = g++
CFLAGS = -Wall -std=c++11

all: server

server: server.o libserver.a
	$(CC) $(CFLAGS) -o server server.o -L. -lserver

server.o: server.cpp
	$(CC) $(CFLAGS) -c server.cpp

libserver.a: libserver.so
	ar rcs libserver.a libserver.so

clean:
	rm -f server server.o