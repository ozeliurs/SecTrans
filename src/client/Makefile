CC = g++
CFLAGS = -Wall -std=c++11

all: client

client: client.o ../lib/libclient.so
	$(CC) $(CFLAGS) -o client client.o -L. -lclient

client.o: client.cpp ../lib/client.h
	$(CC) $(CFLAGS) -c client.cpp client.h

clean:
	rm -f client client.o