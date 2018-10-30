#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  int x=0;

  fork();
  wait(&x);

  if(x)
    printf("I like systems programming %d\n",x);
  else{
    sleep(5);
    printf("I like Java programming\n");
    exit(100);
  }
  exit(0);
}