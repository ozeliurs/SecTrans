PWD = $(shell pwd)
LIB_FLAGS = -Lsrc/lib -Isrc/include -lserver -lclient
OPENSSL_FLAGS = -I/opt/homebrew/opt/openssl@3/include -L/opt/homebrew/opt/openssl@3/lib -lcrypto -Wno-deprecated-declarations

all: client server

# Main
client: build src/client/client.c link
	gcc -o build/client src/client/client.c $(LIB_FLAGS) $(OPENSSL_FLAGS)

server: build src/server/server.c link
	gcc -o build/server src/server/server.c $(LIB_FLAGS) $(OPENSSL_FLAGS)

run_client_list: client
	cd build && ./client -list

run_client_get: client
	cd build && echo "pipi" > ./pipi && ./client -up ./pipi

run_server: server
	cd build && mkdir -p storage && touch storage/caca && ./server

clear: clean

# Tests

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

rsa: build
	gcc -o build/rsa test/lib/rsa.c $(LIB_FLAGS) $(OPENSSL_FLAGS)

secure_bi_client: build
	gcc -o build/secure_bi_client test/lib/secure_bi_client.c $(LIB_FLAGS) $(OPENSSL_FLAGS)

secure_bi_server: build
	gcc -o build/secure_bi_server test/lib/secure_bi_server.c $(LIB_FLAGS) $(OPENSSL_FLAGS)

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

run_secure_bi_server: link secure_bi_server
	cd build && ./secure_bi_server

run_secure_bi_client: link secure_bi_client
	cd build && ./secure_bi_client

run_rsa: link rsa
	cd build && ./rsa

# Utils

build:
	mkdir build

link: build
	ln -sf $(PWD)/src/lib/libserver.so $(PWD)/build/libserver.so
	ln -sf $(PWD)/src/lib/libclient.so $(PWD)/build/libclient.so

clean:
	rm -fr /tmp/crappy_sockets_*.sock build/*