#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
//&&&&&&&&
#include <unistd.h>
#include <arpa/inet.h>
#include "majda.h"
//&&&&&&&&
#define MAX 80 //It was 80 , i change it to 65 , trame length
#define PORT 8040
#define SA struct sockaddr


// Here I am going to include my files
//#include "CrcTransfert.h"
//#include "CrcReceive.h"


//End Of Incuding My files
void func(int sockfd,char *buff)
{	

		printf("TRAM FROM CLIENT %s ",buff);

		write(sockfd, buff, 65); //envoie du msg au serveur

}


int main()
{	
	
	char message[65]; // 8*6 + 6(Rest+'\0')
						

	//loguer de la trame c'est 64 + \0 = 65
	char trame[65] = "0000000000000000000000000000000000000000111101110000000000000000";
	CrcTrasnfert(trame , message);
	

	
	int sockfd, connfd;
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
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the router failed...\n");
		exit(0);
	}
	else
		printf("connected to the router..\n");

	// function for chat
	func(sockfd,trame);

	// close the socket
	close(sockfd);
}


