CC = gcc
CFLAGS = -Wall -Werror

all: client

client: client.c libclient.a
	$(CC) $(CFLAGS) -o client client.c -L. -lclient -Wl,-rpath,. -Wl,-Bstatic -lclient -Wl,-Bdynamic

libclient.a: client.h client.c
	$(CC) $(CFLAGS) -c -o client.o client.c
	ar rcs libclient.a client.o

clean:
	rm -f client libclient.a client.os