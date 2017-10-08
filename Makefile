all: client server tcp_splitter

client:
	cc client.c -o client

server:
	cc server.c -o server

tcp_splitter:
	gcc tcp_splitting_proxy.c -o tcp_splitting_proxy
