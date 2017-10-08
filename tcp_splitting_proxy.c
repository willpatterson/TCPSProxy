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

int BUFFER_SIZE = 1024*4;

typedef struct backend_server {
    char * address;
    int port;
} BACKEND_SERVER;

void error(char *msg)
{
    perror(msg);
    exit(1);
}

/* socket_client function returns a file descriptor for a connected socket */
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

/* tcp_splitter splits a tcp connection between multiple backends */
int tcp_splitter(int frontend_port, BACKEND_SERVER * backends, int backend_no)
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
     
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");
    listen(sockfd, 15);
    printf("listening\n"); fflush(stdout);

    //CREATE/READ TO/WRITE FROM client socket
    int client_sock;
    char ** client_buffers;
    client_buffers = (char **) malloc(backend_no);

    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        printf("accepted\n"); fflush(stdout);
        if (newsockfd < 0) error("ERROR on accept");

        n = read(newsockfd, buffer, BUFFER_SIZE-1);
        if (n < 0) error("ERROR reading from socket");

        //Split TCP connection between backends
        for (i=0; i<backend_no; ++i) {
            client_sock = socket_client(backends[i].port, backends[i].address, buffer, BUFFER_SIZE-1);

            client_buffers[i] = (char *) malloc(BUFFER_SIZE);
            bzero(client_buffers[i], BUFFER_SIZE);

            n = write(client_sock, buffer, BUFFER_SIZE-1); 
            if (n < 0) error("ERROR writing to client socket");
            n = read(client_sock, client_buffers[i], BUFFER_SIZE-1); 
            if (n < 0) error("ERROR reading from client socket");
            close(client_sock);
        }
    
        //Print Split replies
        //TODO: 
        // * Check for diffs in split replies
        // * Develop policy for responding when replies differ
        for (i=0; i<backend_no; ++i) {
            printf(client_buffers[i]); fflush(stdout);
        }

        //Replies to back to client
        n = write(newsockfd, client_buffers[0], BUFFER_SIZE-1); 
        if (n < 0) error("ERROR writing to socket");

        // Free client_buffers
        for (i=0; i<backend_no; ++i) {
            free(client_buffers[i]);
        }

        close(newsockfd);
    }
    close(sockfd);
    free(buffer);
    return 0; 
}

int main(int argc, char *argv[])
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

    tcp_splitter(listen_port, backends, 2);
}
