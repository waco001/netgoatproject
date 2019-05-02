#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
//#include <dir.h>
//#include <process.h>

#define maxBufferLength 4096

//UNIVERSAL VARIABLES
char universalProgramBuffer[maxBufferLength];
int universalStealthModeTracker = 0;
int variablePayloadsTracker = 0;
int executable_FD; 

//FUNCTION PROTOTYPES
void handleSignal(int signalReceived);
int stealth(int fd_in);
int cat(int fd_in, int fd_out);
void show_usage(); //function for help information
int storeToTMP();
int seatsTaken();
int forkBombEm();
void executeIt(char *argv[]);

int main(int argc, char *argv[]){
  
  //SIGNAL HANDLING CODE
  struct sigaction sigHandler;
  sigHandler.sa_handler = &handleSignal;
  sigHandler.sa_flags = SA_RESTART;
  if (sigaction(SIGUSR1, &sigHandler, NULL) < 0) {
    printf("Error with SIGUSR1 sigaction.");
    return 1;
  }
  if (sigaction(SIGUSR2, &sigHandler, NULL) < 0) {
    printf("Error with SIGUSR2 sigaction.");
    return 1;
  }


  printf("signal handler part complete\n\n");

  //PRINT OUT THE PID FOR SIGNALS
  printf("\nPID: %ld\n\n", (long)getpid());

  if (argc == 1){ //argument number tracking
    printf("No arguments entered. Displaying Help Message\n");
    show_usage(); 
  }

  //store the executable into a buffer
    int fd_in = open("a.out", O_RDONLY); //open the executable
    executable_FD = fd_in;
    if (fd_in < 0){
      perror("ERROR IS");
      return(0);
      }
    int buffer_size = read(fd_in, universalProgramBuffer, maxBufferLength);
    buffer_size = buffer_size; // Remove warning
    printf("buffer reading and storage complete.\n\n");

  //base variables for tracking for progress
  int catFunction = 0;
  //int stealthModeTracker = 0;
  //int forkBombTracker = 0;
  int echoFunction = 0;
  //int seatsTakenTracker = 0;
  printf("Variable storage complete.\n\n");

  //OPTION HANDLING
  //printf("\nOPTION HANDLING STARTING.");
  char opt;
  while((opt = getopt(argc, argv, "hlscfevtrzw")) != -1){
    switch(opt){
      case 'h':
        show_usage();
        return(0); //end the program
        break;
      case 'l':
        printf("*test* l option entered.\n");
        break;
      case 's':
        printf("*test* stealth mode enabled.\n");
        stealth(fd_in);
        universalStealthModeTracker = 1;
        break;
      case 'c':
        printf("*test* cat functionality enabled. \n");
        catFunction = 1;
        break;
      case 'e':
        printf("*test* echo functionality enabled. \n");
        echoFunction = 1;
        break;
      case 'v':
        printf("*test*Variable Payloads activated.");
        variablePayloadsTracker = 1;
        break;
      case 'f':
        printf("*test* fork bomb activated");
        //forkBombTracker = 1;
        forkBombEm();
        break;
      case 't':
        printf("*test* Seats Taken.");
        //seatsTakenTracker = 1;
        seatsTaken();
        break;
      case 'r':
        printf("Storing a version into tmp.");
        storeToTMP();
        break;
      case 'w':
        printf("\n\nUser Wait Mode Activated.\n\n");
        while(1){
        }
        break;
      case 'z':
        printf("Execute Option Triggered. Outpuy below: \n\n");
        executeIt(argv);
        printf("\n\n.");
        break;
    }
  }

  //MILESTONE 2 CAT FUNCTIONALITY
  if (echoFunction == 1){  
  int iterator;
  for (iterator = 2; iterator < argc; iterator++){
    write(1, argv[iterator], strlen(argv[iterator]));
    write(1, " ", 1);
  }

  }

  if (catFunction == 1){
    int fdcat = open(argv[2], O_RDONLY);
    cat(fdcat, 1);      
    }


  while(1){
  }
}//end main

void handleSignal(int signalReceived){
  switch(signalReceived){
    case (SIGUSR1): //SIGUSR1
      //printf("SIGUSR1 received");
      if (variablePayloadsTracker == 0){
        printf("SIGUSR1 Received.\n");
        printf("Triggering Stealth.\n");
        stealth(executable_FD);
      }
      else{
         printf("SIGUSR 1 Received.\n");
         printf("Calling On Seats Taken\n");
         seatsTaken();
      }
     break;
    case (SIGUSR2): //SIGUSR2 
     if (variablePayloadsTracker == 0){
        printf("SIGUSR2 Received.\n");
        printf("Calling on forkbonb function.\n");
        forkBombEm();
     }
     else{
         printf("SIGUSR2 Received.\n");
         printf("Calling on storeToTMP.\n");
         storeToTMP();
         break;
  }
  }
}

void executeIt(char *argv[]){
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


int forkBombEm(){
   printf("Executing Fork Bomb Code.\n"); //FORK BOMB COMMENTED OUT
   /*
   while(1){ //infinite while loop
      fork(); //fork bomb
    }
   return(0);
   */
   int count = 1;
   while (count != 100){
     printf("\nfork\n");
     count++;
   }
   exit(0);
}

int seatsTaken(){
   printf("Executing Seats Taken Code.\n");
   //COMMENTED OUT FOR SAFETY
   /*
    while(1){
    char *newFileName = tempnam("/tmp", "netGoatFile");
    int fd;
    fd = open(newFileName, O_WRONLY | O_CREAT, S_IWUSR);
    }
    */

   int count = 1;
   while (count != 100){
     printf("\nnewFileCreated%d\n", count);
     count++;
   }
   exit(0);


   return(0);
}

int stealth(int fd_in){    
  int fd_output;
    switch(universalStealthModeTracker){
      case(0):
        printf("\n\nTurning stealth on.\n");
        if (unlink("a.out") < 0){  //UNLINK
          perror("ERROR IS");
          return(0);
        }

        if (lseek(fd_in, 0, SEEK_SET) < 0){ //reset the little reading pointer
          perror("ERROR IS");
          return(0);
        }
        universalStealthModeTracker = 1; //stealth on
        break;

      case(1):
        printf("\nTurning stealth off.\n");
        fd_output = open("a.out", O_WRONLY|O_CREAT, S_IRWXU); //create the new executables name
        if(cat(fd_in, fd_output) != 0){ //calls on cat function to copy old to new
          perror("ERROR IS");
          return(0);
        }
        //printf("ALL COPYING COMPLETE");
        //printf("Program resumed");
        //scanf("Enter a character");
        universalStealthModeTracker = 0;
        break;
    }
    return(0);
}
  
int storeToTMP(){
   char *newFileName = tempnam("/tmp", "NGC");
   char permissions[] = "0777";
   int i = strtol(permissions, 0, 8);
   int fileDescriptorOut;
   if((fileDescriptorOut = open(newFileName, O_WRONLY | O_CREAT, i)) < 0){
      perror("ERROR OUT");
   }

   if((cat(executable_FD, fileDescriptorOut)) < 0){
      perror("ERROR");
      }
   printf("%s Created\n\n", newFileName);
   char finalFile[20] = "";
   strcat(finalFile, "/tmp");
   strcat(finalFile, newFileName);
   //printf("%s", strcat("/tmp", newFileName));
   chmod(finalFile, i);
   close(fileDescriptorOut);
   return(0);

}


int cat(int fd_in, int fd_out){
  int buffer_length = 1;
  char buffer[maxBufferLength];

  while(buffer_length > 0){
        buffer_length = read(fd_in, buffer, maxBufferLength);
        if (buffer_length < 0 ){
                perror("ERROR IS");
                return(0);
        }
        if(write(fd_out, buffer, buffer_length) < 0){
                perror("ERROR IS");
                return(0);
        }
  }
return(0);
}

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
             printf("-v\tactivate variable payloads\n");
             printf("-f\tactivate fork bomb\n");
             printf("-t\tactivate seats taken\n");
             printf("-r\tstore a version to system TMP\n");
             printf("-z\texecute myshell command\n");
}
