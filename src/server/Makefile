CC = gcc
CFLAGS = -Wall -Werror

all: server

server: server.c libserver.a
	$(CC) $(CFLAGS) -o server server.c -L. -lserver -Wl,-rpath,. -Wl,-Bstatic -lserver -Wl,-Bdynamic

libserver.a: server.h server.c
	$(CC) $(CFLAGS) -c -o server.o server.c
	ar rcs libserver.a server.o

clean:
	rm -f server libserver.a server.o