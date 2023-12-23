CC = g++
CFLAGS = -Wall -std=c++11

all: client

client: client.o libclient.a
	$(CC) $(CFLAGS) -o client client.o -L. -lclient

client.o: client.cpp
	$(CC) $(CFLAGS) -c client.cpp

libclient.a: libclient.so
	ar rcs libclient.a libclient.so

clean:
	rm -f client client.o