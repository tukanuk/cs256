#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

int buildCommand (char *com, char *comArgcv[10]);   
void parent(int *fd, char *argv[]);
void child(int *fd, char *argv[]);    

int main(int argc, char *argv[]){
  int fd[2];
  
  // tokenize argv[]
  char *comArgv1[20], *comArgv2[20];
  char *com1, *com2;
  int i=0;

  com1 = strtok(argv[1], "|");
  com2 = strtok(NULL, "|");

  printf("com1: %s\ncom2: %s\n", com1, com2);

  buildCommand(com1, comArgv1);
  buildCommand(com2, comArgv2);

  if(pipe(fd)==-1){
    perror("Cannot create pipe: ");
    exit(1);
  }
  if(fork() > 0)
    parent(fd, argv);
  else
    child(fd, argv);
}

void parent(int *fd, char *argv[]){ // A writer
  close(fd[0]);
  dup2(fd[1], 1); // 1 is the standard output
  close(fd[1]); // close original file descriptor
  if(execvp(argv[0], argv) == -1){
    perror("Cannot exec: ");
    exit(3);
  }
}
void child(int *fd, char *argv[]){ // A reader
  close(fd[1]);
  dup2(fd[0], 0); // 0 is the standard input
  close(fd[0]); // close original file descriptor
  if(execvp(argv[0], argv) == -1){
    perror("Cannot exec: ");
    exit(3);
  }
}

int buildCommand (char *com, char *comArgv[10])
{
    int i=0;
    
    comArgv[i] = strtok(com, " ");
    printf("-> %s\n", comArgv[i]);
    while (comArgv[i])
    {
        i++;
        comArgv[i] = strtok(NULL, " ");
        printf("      %s\n", comArgv[i]);
    }
    return 0;
}   