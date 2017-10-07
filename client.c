#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) //Args: Hostname, Port Number
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr; //Structures Defined in netlib.h
    struct hostent *server;       //

    char buffer[256];

    //Check Args
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    //Open Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET creates IP socket, SOCK_STREAM creates TCP socket
    if (sockfd < 0) 
        error("ERROR opening socket");

    //Read/Parse Args
    portno = atoi(argv[2]);
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    printf("%s", server->h_name);

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    //Attempt to connect 
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    //Read Message
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer)); //Write Message from buffer to socket
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255); //Read Socket into Buffer
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer); //Print Response
    return 0;
}
