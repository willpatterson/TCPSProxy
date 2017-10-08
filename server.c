/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])  //Args Port
{
     printf("test\n");
     fflush(stdout);
     int sockfd, newsockfd, portno, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     //Check Args
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     //Open Socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     
     //Binds socket to address and port (port contained in serv_addr
     if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd, 15); //Listen on bound socket
     printf("listening\n");
     fflush(stdout);

     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen); //blocks process until client connects
     printf("accepted\n");
     fflush(stdout);
     if (newsockfd < 0) 
          error("ERROR on accept");

     bzero(buffer,256);
     n = read(newsockfd,buffer,255); //Reads from socket into buffer
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18); //Replies to client by writing back into socket
     if (n < 0) error("ERROR writing to socket");
     return 0; 
}
