/* The worst TCP proxy ever written */

#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>

int BUFFER_SIZE = 512;

typedef struct backend_server {
    char * address;
    int port;
} BACKEND_SERVER;

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int socket_client(int portno, char *hostname, char *message, int message_len) 
{
    int sockfd, n;

    struct sockaddr_in serv_addr; //Structures Defined in netlib.h
    struct hostent *server;       //

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET creates IP socket, SOCK_STREAM creates TCP socket
    if (sockfd < 0) error("ERROR opening socket");

    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    //Attempt to connect 
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    return  sockfd;
}

int socket_server(int frontend_port, BACKEND_SERVER * backends, int backend_no)
{
     int sockfd, newsockfd, clilen;
     struct sockaddr_in serv_addr, cli_addr;
     int n, i;

     char * buffer;
     buffer = (char *) malloc(BUFFER_SIZE);
     bzero(buffer,BUFFER_SIZE);

     //Open Socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(frontend_port);
     
     //Binds socket to address and port (port contained in serv_addr
     if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd, 15); //Listen on bound socket
     printf("listening\n"); fflush(stdout);

     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen); //blocks process until client connects
     printf("accepted\n"); fflush(stdout);
     if (newsockfd < 0) error("ERROR on accept");

     n = read(newsockfd, buffer, BUFFER_SIZE-1); //Reads from socket into buffer
     if (n < 0) error("ERROR reading from socket");

     //CREATE/READ TO/WRITE FROM client socket
     int client_sock;
     char ** client_buffers;
     client_buffers = (char **) malloc(backend_no);

     //Split TCP connection between backends
     for (i=0; i<backend_no; ++i) {
         client_sock = socket_client(backends[i].port, backends[i].address, buffer, BUFFER_SIZE-1);

         client_buffers[i] = (char *) malloc(BUFFER_SIZE);
         bzero(client_buffers[i], BUFFER_SIZE);

         n = write(client_sock, buffer, BUFFER_SIZE-1); 
         if (n < 0) error("ERROR reading from client socket");
         n = read(client_sock, client_buffers[i], BUFFER_SIZE-1); 
         if (n < 0) error("ERROR writing to client socket");
         close(client_sock);
     }
     
     for (i=0; i<backend_no; ++i) {
         printf(client_buffers[i]); fflush(stdout);
     }

     n = write(newsockfd, buffer, BUFFER_SIZE-1); //Replies to client by writing back into socket
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0; 
}

int main(int argc, char *argv[])  //Args Port
{
    int listen_port = 10001;
    char * loopback = "127.0.0.1";
    BACKEND_SERVER * backends;
    backends = (BACKEND_SERVER*) malloc(2);

    //Redis 0
    backends[0].address = (char *) malloc(10);
    strcpy(backends[0].address, loopback);
    backends[0].port = 6379;

    //Redis 1
    backends[1].address = (char *) malloc(10);
    strcpy(backends[1].address, loopback);
    backends[1].port = 6380;

    socket_server(listen_port, backends, 2);
}
