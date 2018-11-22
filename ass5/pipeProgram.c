#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define DEBUG 0

int buildCommand (char *com, char *comArgcv[10]);   
void parent(int *fd, char *argv[]);
void child(int *fd, char *argv[]);    

int main(int argc, char *argv[]){
  int fd[2];
  int status;
  
  // tokenize argv[]
  char *comArgv1[20], *comArgv2[20];
  char *com1, *com2;
  int i=0;

  com1 = strtok(argv[1], "|");
  com2 = strtok(NULL, "|");

  // check the parse in two strings
  if (DEBUG) printf("com1: %s\ncom2: %s\n", com1, com2);

  // parses the two strings into arrays
  buildCommand(com1, comArgv1);
  buildCommand(com2, comArgv2);

  // checks the parse into two command arrays 
  if (DEBUG) printf("1st command: %s flag: %s\n", comArgv1[0], comArgv1[1]);
  if (DEBUG) printf("2nd command: %s flag: %s\n", comArgv2[0], comArgv2[1]);

  if(pipe(fd)==-1){
    perror("Cannot create pipe: ");
    exit(1);
  }
  if(fork() > 0)
  {
    parent(fd, comArgv1); // execute the first command (pass through pipe to second)
  }
  else
  {
    child(fd, comArgv2); // execute the second command
  }
}

void parent(int *fd, char *argv[]){ // A writer
  close(fd[0]);
  dup2(fd[1], 1);   // 1 is the standard output. this passes stdout through the pipe (redirect)
  close(fd[1]);     // close original file descriptor
  if(execvp(argv[0], argv) == -1){
    perror("Cannot exec: ");
    exit(3);
  }
}
void child(int *fd, char *argv[]){ // A reader
  close(fd[1]);
  dup2(fd[0], 0);     // 0 is the standard input. This passes the pipe as stdin. 
                      // (The pipe takes the place of the keyobard).
  close(fd[0]);       // close original file descriptor
  if(execvp(argv[0], argv) == -1){
    perror("Cannot exec: ");
    exit(3);
  }
}
/* buildCommand
 * INPUT:  unparsed command, array to store parsed command
 * OUTPUT: returns parsed command in passed array
 */
int buildCommand (char *com, char *comArgv[10])
{
    int i=0;
    
    comArgv[i] = strtok(com, " ");
    if (DEBUG) printf("-> %s\n", comArgv[i]);
    while (comArgv[i])
    {
        i++;
        comArgv[i] = strtok(NULL, " ");
        if (DEBUG) printf("      %s\n", comArgv[i]);
    }
    return 0;
}   