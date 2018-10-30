#include <unistd.h>
#include <stdio.h>
// #include <stdlib.h>

//int main(int argc, char *argv[]){
//   int pid;
//   printf("Only one process\n");
//   pid = fork();
//   if(pid == -1){
//     perror("impossible to fork");
//     exit(1);
//     }
// if(pid > 0)
//     printf("I am the parent, pid=%d\n", getpid());
//   else
//     if(pid == 0)
//       printf("I am the child, pid=%d\n", getpid());

// for (int i=1;i<=3;i++)
//     fork();
// printf("I'm here\n");

#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int i = fork();

    if (i == 0) 
    {
        printf("I am blue\n");
    }
    else if (i > 0)
    {
        printf("I am green\n");
    }

    return 0;
}