CC = gcc
CFLAGS = -Wall -Werror

all: server

server: server.cpp libserver.a
	$(CC) $(CFLAGS) -o server server.cpp -L. -lserver -Wl,-rpath,. -Wl,-Bstatic -lserver -Wl,-Bdynamic

libserver.a: server.h server.cpp
	$(CC) $(CFLAGS) -c -o server.o server.cpp
	ar rcs libserver.a server.o

clean:
	rm -f server server.o libserver.a