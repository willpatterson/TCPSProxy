all: tcp_splitter

client: ./src/basic_client_template.c
	mkdir -p ./bin
	gcc ./src/basic_client_template.c -o ./bin/client

server: ./src/basic_server_template.c
	mkdir -p ./bin
	gcc ./src/basic_server_template.c -o ./bin/server

tcp_splitter: ./src/tcp_splitting_proxy.c
	mkdir -p ./bin
	gcc ./src/tcp_splitting_proxy.c -o ./bin/tcp_splitting_proxy

clean:
	rm ./bin/*
