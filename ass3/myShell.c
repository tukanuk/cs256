#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/wait.h>

#define LINELENGTH 255
#define NUMBER_OF_COMMANDS 10
#define LENGTH_OF_COMMAND 255

int readLine(int, char *, int);

int main(int argc, char *argv[])
{
  int fd1;                          // file
  int status=0, n;                  // commands with no arguments
  char lineBuff[LINELENGTH];        // line buffer
  char *myCommand[NUMBER_OF_COMMANDS];
  int lineNum = 0;
  int i, j;
  int numChar;                    // number of character on line

  // check the file
  if ( (fd1 = open(argv[1], O_RDONLY)) == -1)
  {
      perror("File opening problem. Usage: myShell <myScriptFile>\n");
      exit(1);
  }

  while(1)
  {   
    numChar = readLine(fd1, lineBuff, LINELENGTH);
    if ( numChar <= 0)
    {
      break;
    } 

    lineBuff[numChar -1]='\0'; // no \n, add string term
    i = j = 0; 

    if (strncmp(lineBuff, "#", 1) != 0)
    { 
      myCommand[i] = (char *) malloc(25);
      while(sscanf(lineBuff+j, "%s", myCommand[i]) == 1)
      {
        j+= strlen(myCommand[i]);
        while (lineBuff[j] == ' ')
        {
          j++;
        }
        i++;
        myCommand[i] = (char *) malloc(25);
      }
      myCommand[i]=NULL;

      if(!fork() )
      {
        if(execvp(myCommand[0], myCommand) == -1)
        {
          perror("child process");
          exit(3);
        }
      }
      wait(&status);
    }
  }

  if (numChar == -1)
  {
    perror("Read error");
    exit(1);
  }

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
