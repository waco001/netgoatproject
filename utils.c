/*

SY204 Utilities
Version 1.0
Last update: 02/16/18

*/

#include <stdio.h>   // For printf() and perror()
#include <stdlib.h>  // For exit()
#include <errno.h>   // For errno
#include <string.h>  // For strerror()
#include "utils.h"

// Utility-01 ----------------------------------------------------------------
/*

Name: Error handling utility

Description: This utility takes the prefix message you want to apply (text),
preserves the value in errno, and using perror(), appends the plain-text version
of errno to the prefix and outputs that stderr.  The utility will also return
the numerical value that was stored in errno, or, you can choose to exit your
program based on the value in exitCmd. The two options for exitCmd (EXIT and
NOEXIT) are defined in utils.h

*/

int errExit(char *text, int exitCmd) {

   int errnum = errno;
   perror(text);
   if (exitCmd == EXIT) {
      exit(errnum);
   }
   return errnum;

}

// ===========================================================================

// parse a command line into: argc, argv, and the actual command to execute
struct command_t parseCommandline(char *commandLine) {
   struct command_t thisCommand;
   int i = 1;
   char *position = NULL;

   // parse the command line into its argv parts
   thisCommand.cmd = strtok(commandLine," "); // the actual executable command (with path)
   while ((thisCommand.argv[i] = strtok(NULL," ")) != NULL) i++;
   thisCommand.argc = i;

   // determine the basename of the command
   position = strrchr(thisCommand.cmd,'/'); // find the / in the command
   if (position == NULL) thisCommand.argv[0] = thisCommand.cmd; // not found
   else thisCommand.argv[0] = position+1; // found so move 1 past it

   return thisCommand;
}
