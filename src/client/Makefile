CC = gcc
CFLAGS = -Wall -Werror

all: client

client: client.cpp libclient.a
	$(CC) $(CFLAGS) -o client client.c -L. -lclient -Wl,-rpath,. -Wl,-Bstatic -lclient -Wl,-Bdynamic

libclient.a: client.h client.cpp
	$(CC) $(CFLAGS) -c -o client.o client.c
	ar rcs libclient.a client.o

clean:
	rm -f client client.o libclient.a