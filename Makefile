PWD = $(shell pwd)
LIB_FLAGS = -Lsrc/lib -Isrc/include -lserver -lclient

all: simple_server simple_client advanced_server advanced_client

simple_server:
	gcc -o simple_server test/lib/simple_server.c $(LIB_FLAGS)

simple_client:
	gcc -o simple_client test/lib/simple_client.c $(LIB_FLAGS)

advanced_server:
	gcc -o advanced_server test/lib/advanced_server.c $(LIB_FLAGS)

advanced_client:
	gcc -o advanced_client test/lib/advanced_client.c $(LIB_FLAGS)

run_simple_server: link simple_server
	./simple_server

run_simple_client: link simple_client
	./simple_client

run_advanced_server: link advanced_server
	./advanced_server

run_advanced_client: link advanced_client
	./advanced_client

link:
	ln -sf $(PWD)/src/lib/libserver.so $(PWD)/libserver.so
	ln -sf $(PWD)/src/lib/libclient.so $(PWD)/libclient.so

clean:
	rm -f libserver.so libclient.so /tmp/crappy_sockets_*.sock ultimate simple_server simple_client advanced_server advanced_client

test: ultimate simple_server simple_client