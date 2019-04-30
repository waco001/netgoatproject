/*

SY204 Utilities
Version 1.0
Last update: 02/16/18

*/

// If multiple source files (for a single project) all include "utils.h", this
// prevents collisions where each tries to (re)define the prototypes and macros.
#ifndef __UTILS_H

   // Macros

   #define __UTILS_H
   #define EXIT 1    // For errExit
   #define NOEXIT 0  // For errExit

   // Prototypes

   // Error handling utility
   int errExit(char *text, int exitCmd);

   // for parsing a command line into arguments
   #define MAXARGS 10
   struct command_t {
      char *cmd;
      char *argv[MAXARGS]; // no more than 10 args ... for now
      int argc;
   };

   // command line parsing utility
   struct command_t parseCommandline(char *commandLine);

#endif
