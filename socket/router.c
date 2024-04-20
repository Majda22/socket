#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include "majda.h"
//&&&&&&&&
#define MAX 80 //It was 80 , i change it to 65 , trame length
#define PORTCLIENT 8040
#define PORT 8075
#define SA struct sockaddr

//&&&&&&&&&
#include <unistd.h>
#include <arpa/inet.h>
//&&&&&&&&&



//mYsRC Code
//#include "CrcTransfert.h"
//#include "CrcReceive.h"

// Function designed for chat between client and server.



void funcServer(int connfd,char *trame)
{
	char buff[MAX];
		//bzero(buff, MAX);

		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));
		// print buffer which contains the client contents
		
		printf("\n--TRAME FROM SERVER %s ",buff);
		if(CrcRecieve(buff)){
		   printf("\n--TRAME Successfully received");
		}else{
		   printf("\n--TRAME Failed in receiving");
		}   
		strcpy(trame,buff);
		bzero(buff, MAX);
	


}
void funcClient(int sockfd,char *buff)
{	

		printf("TRAM FROM CLIENT %s ",buff);

		write(sockfd, buff, 65); //envoie du msg au serveur

}

// Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORTCLIENT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// Function for chatting between client and server
	char trame[65];
	funcServer(connfd,trame);

	// After chatting close the socket
	close(sockfd);



		int sockfd2, connfd2;
	struct sockaddr_in servaddr2, cli2;

	// socket create and verification
	sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd2 == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr2, sizeof(servaddr2));

	// assign IP, PORT
	servaddr2.sin_family = AF_INET;
	servaddr2.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr2.sin_port = htons(8075);


	// connect the client socket to server socket
	if (connect(sockfd2, (SA*)&servaddr2, sizeof(servaddr2)) != 0) {
		printf("connection with the router failed...\n");
		exit(0);
	}
	else
		printf("connected to the router..\n");

	// function for chat
	funcClient(sockfd2,trame);

	// close the socket
	close(sockfd2);
}

