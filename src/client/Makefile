CC = g++
CFLAGS = -Wall -std=c++11

all: client

client: client.o libclient.so
	$(CC) $(CFLAGS) -o client client.o -Wl,-Bstatic -l:libclient.so

client.o: client.cpp
	$(CC) $(CFLAGS) -c client.cpp

clean:
	rm -f client client.o