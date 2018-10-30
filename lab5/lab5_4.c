#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/wait.h>

int readLine(int, char *, int);

int main(int argc, char *argv[]){   // To execute
  int status=0, n;                  // commands with no arguments
  char line[255];

  if (argc > 1)
  {
    char *command = argv[1];
    char *argument = "";
    if (argv[2]) argument = argv[2];

    printf("command: %s\n", command);
    printf("argument: %s\n", argument);
    char str[50];
    sprintf(str, "%s %s", command, argument);
    printf("%s\n",str);
    if(!fork()) 
    {
        execlp(command, command, argument, NULL);
    }
  }
  else {
    char prompt[30]="Enter your command here> ";
    while(1){
        write(STDIN_FILENO, prompt, 25);
        n=readLine(STDIN_FILENO, line, 255);
        if( n <= 0) // read a command
        break;

        line[n-1]='\0';     // get rid of \n and add '\0'
                            // for string manipulation
        if(!fork()) 
        execlp(line, line, NULL);

        wait(&status);
    }
  }
  if(n==-1)
    perror("Reading error ");

  exit(0);
}

int readLine(int fd, char *buff, int n){
  int i=0, m;

  while(i<n && (m=read(fd, &buff[i], 1))==1){
    if(buff[i]=='\n')
       return(i+1);
    i++;
  }
  if(m == -1)             // Error, return -1
     return(-1);
  else
     return(i);           // number of characters read
}	
