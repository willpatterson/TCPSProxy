all: client server tcp_proxy

client:
	cc client.c -o client

server:
	cc server.c -o server

tcp_proxy:
	gcc tcp_proxy.c -o tcp_proxy
