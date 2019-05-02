/*
 * Name: MIDN Li
 * Alpha:213924
 * Course: SY204 - Sys Prgm & OS Fund
 * Assignment: NETCAT
 *
 * Description: netcat will act as either a server or client and will assist in sending or receiving communications from one machine to another.
 *
 * Resources: <Cite any resources used in a style similar to MLA>
 */

// Required Includes
// New Uses
#include <netinet/in.h>  // Network Internet Library: IPPROTO_*
#include <arpa/inet.h>
// Previous Uses
#include <stdlib.h>  // Standard Library: EXIT_*, exit(3)
#include <unistd.h>  // UNIX Standard Library: getopt(3)
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
// Global Constants
// Network Communications
#define UNSET_MODE      000
#define CLIENT_MODE     001  // Default
#define SERVER_MODE     002
#define CLNT_SERV_MASK  003
#define IPv4_MODE       004  // Default
#define IPv6_MODE       010
#define NET_MASK        014
#define TCP_MODE        020  // Default
#define UDP_MODE        040
#define TRANS_MASK      060
char flgMode = CLIENT_MODE | IPv4_MODE | TCP_MODE;

// Function Prototypes

// main Function: <A general high-level description about what the function is designed to accomplish>
int main( int argc, char *argv[]) {
	// Declare Required Variables
   int option;	
   int readvalue; 
   char buffer[1000];
   int sockfd;
   int sockfd2;
   int port;
 
  
     struct sockaddr_in server_addR, client_addR;
     struct sockaddr_storage store_addR;
      socklen_t length;

       
  
if(strcmp(argv[1], "-l") != 0 && strcmp(argv[1], "-h") != 0){ //if not -l or -h, works as client  
if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
          perror("Error");}
          port = atoi(argv[2]); 
         client_addR.sin_port = htons(port);
         client_addR.sin_family = AF_INET;
               
         inet_pton(AF_INET, argv[1], &client_addR.sin_addr);
         
         if(connect(sockfd, (struct sockaddr*)&client_addR, sizeof(client_addR)) == 0){
            write(1, "Connected to Server\n", 20);}
       
        while(1){ //send and receive from the server
         readvalue = read( 0 , buffer, 1000);
         send(sockfd, buffer, readvalue, 0);
         int value2 = recv(sockfd, buffer, 1000, 0);
         write(1, buffer, value2);}
         close(sockfd);
   } 

    opterr = 0;
   
	while ( ( option = getopt(argc, argv, "hl:")) != -1 ) {
		switch (option) {
			case 'h': // Help Option
         printf("This is netkitty. Can be used as either a client or a server to communicate with each other \n");
         printf("USAGE: ./[executable] [option -l] [port number]\n");
         printf("./[executable] [IP Address] [port number]\n");
         printf("For help, use -h\n");
         
		   break;
         case 'l':   //to be used as server
            if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
            perror("ERROR");}
        
          port = atoi(argv[2]);
         server_addR.sin_port = htons(port);
         
         server_addR.sin_family = AF_INET;
         server_addR.sin_addr.s_addr = INADDR_ANY;
        
        
                  
        if( (bind(sockfd, (struct sockaddr*) &server_addR, sizeof(server_addR))) ==-1){
           perror("ERROR");}
           
         
         if(listen(sockfd, 10) == 0){
            printf("listening on port %d\n", port);}
       
        length = sizeof(store_addR);
        if((sockfd2 = accept(sockfd, (struct sockaddr*)&store_addR, &length)) == -1){
         perror("ERROR");}
        else{
           write(1, "Connection established!\n", 24);}
       
         while(1){   //send and receive from client
         readvalue = read( 0 , buffer, 1000);
         send(sockfd2, buffer, readvalue, 0);
         int value2 = recv(sockfd2, buffer, 1000, 0);
         write(1, buffer, value2);}
        close(sockfd2);
        
         break; 
	}
}
	// Return to Caller
	return EXIT_SUCCESS;
}
