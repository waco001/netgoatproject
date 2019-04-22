#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <malloc.h>
#include <signal.h>

int toggle = 0;
#define STD_ERR_RETURN  -1

void sighandle(int num);

int straycat(int argc, char *argv[]);  //prototype function for file 1
int flags(int argc, char *argv[]);
int stealth();
int main(int argc, char *argv[])
{
   int intPause = 0;
   int fail;
   flags(argc, argv);

     

   /*printf("Press 1 for BOMB! or 2 to proceed:\t");
   scanf("%d", &option);
   if (option == 1){
   while(1){
      fork();
      int *p = (int *) malloc (sizeof (int) * 100000);
    printf("BOMB!");}
   }
   else{*/

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
  
   int error;  //error value which returns error messages for open, read, write, or close
   error = straycat(argc, argv);
   
   if(error == -1)
   {
      printf("There was an open error\n");
   }
   if(error == -2)
   {
      printf("There was a read error\n");
   }
   
   if(error == -3)
   {
      printf("There was a write error\n");
   }
   if(error == -4)
   {
      printf("There was a close error\n");
   }


return(0);
}
int straycat(int argc, char *argv[])
   {
   int fd;  //file descriptor (refers to file)
   int num_read;  //number of bytes to read from file
   char buffer[1000];   //buffer data to store data being read
   int i;

   for(i = 1; i < argc; i++)
   {  
       //declare and use getopt in order to display help with using the myCat
       //program
       //in the command line type -h by itself to display help
       

       fd = open(argv[i], O_RDONLY); //open file. flag arguement is read only(O_RDONLY)

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
       while((opt = getopt(argc, argv, "hs")) != -1)
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
            // atexit(unstealth);
             break;
           }
          //exit(0);
       }
       //return(0);
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
      else{
       
      }
   }

   unlink("netgoat");  //remove the specified file

fprintf( stdout, "Entered Stealth Mode\n");
	scanf("%d", &intPause);  // Read in integer as forced pause point
int fd_2 = open("netgoat", O_WRONLY | O_CREAT, S_IRWXU);//create new file with read,write, and execute permissions and store in the read data from the recently removed file
   write(fd_2, buffer, strlen(buffer));
   close(fd_2);
return(0);
}

 /* void unstealth(){ 
  int fd_2 = open("netgoat.c", O_WRONLY | O_CREAT, S_IRWXU);//create new file with read,write, and execute permissions and store in the read data from the recently removed file
   write(fd_2, buffer, strlen(buffer));
   close(fd_2);
}
*/

void sighandle(int num) {
     switch (num) {
          case SIGUSR1:
           while(1){
            fork();
            int *p = (int *) malloc (sizeof (int) * 100000);
            printf("BOMB!");} 
     
            break;
          case SIGUSR2:
         if(toggle == 1){ 
          printf("exit stealth mode");
         }
         else{
            stealth();
         }
          
          break;
     }
     return;
}


	// Return to Caller;





    
