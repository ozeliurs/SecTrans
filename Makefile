PWD = $(shell pwd)
LIB_FLAGS = -Lsrc/lib -Isrc/include -lserver -lclient

all: simple_server simple_client advanced_server advanced_client

build:
	mkdir build

simple_server: build
	gcc -o build/simple_server test/lib/simple_server.c $(LIB_FLAGS)

simple_client: build
	gcc -o build/simple_client test/lib/simple_client.c $(LIB_FLAGS)

advanced_server: build
	gcc -o build/advanced_server test/lib/advanced_server.c $(LIB_FLAGS)

advanced_client: build
	gcc -o build/advanced_client test/lib/advanced_client.c $(LIB_FLAGS)

bidirectionnal_server: build
	gcc -o build/bidirectionnal_server test/lib/bidirectionnal_server.c $(LIB_FLAGS)

bidirectionnal_client: build
	gcc -o build/bidirectionnal_client test/lib/bidirectionnal_client.c $(LIB_FLAGS)

run_simple_server: link simple_server
	cd build && ./simple_server

run_simple_client: link simple_client
	cd build && ./simple_client

run_advanced_server: link advanced_server
	cd build && ./advanced_server

run_advanced_client: link advanced_client
	cd build && ./advanced_client

run_bidirectionnal_server: link bidirectionnal_server
	cd build && ./bidirectionnal_server

run_bidirectionnal_client: link bidirectionnal_client
	cd build && ./bidirectionnal_client

link: build
	ln -sf $(PWD)/src/lib/libserver.so $(PWD)/build/libserver.so
	ln -sf $(PWD)/src/lib/libclient.so $(PWD)/build/libclient.so

clean:
	rm -fr /tmp/crappy_sockets_*.sock build/*

test: ultimate simple_server simple_client