
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void TTIN_handler(){
  printf("Attempted to read from keyboard\n");
exit(22); }
int main(int argc, char *argv[]){
  int i, status, pid;
  if(!(pid=fork())){
    signal(SIGTTIN, TTIN_handler);
    setpgid(0, getpid());
    printf("Enter a value> \n");
    scanf("%d", &i);
    
  }else{
    wait(&status);
    if(WIFEXITED(status))
     printf("Exit status=%d\n",WEXITSTATUS(status));
    else
     printf("signaled by =%d\n",WTERMSIG(status));
  }
}
