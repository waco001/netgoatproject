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
       while((opt = getopt(argc, argv, "hc:sfe:")) != -1)
       {
          switch(opt)
          {
             case 'h':
             printf("NAME\n\n");
             printf("netgoat\n\n");
             printf("SYNOPSIS\n\n");
             printf("netgoat [file] ...\n\n");
             printf("DESCRIPTION\n\n");
             printf("Bunch of stuff\n\n");
             printf("-h\tdisplay this help\n");
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
    execvp(argv[optind], &argv[optind]);
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





    
