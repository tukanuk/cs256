#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

  for (int i=1; i<=4; i++)
    if(fork()>0)
      printf("Hi %d\n", i);

    exit(0);
}