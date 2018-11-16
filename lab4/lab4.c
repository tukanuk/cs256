#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    int pid = fork();
    
    if (pid == 0)
    {
        printf("I'm child one\n");
        printf("My PID is: %d\n", getpid());
        printf("My PPID is: %d\n\n", getppid());
        
    }

    if (pid > 0) 
    {
        
        int pid2 = fork();
        sleep(1);
        if (pid2 > 0)
        {
            printf("I'm the parent. My pid is: %d\n", getpid());
            printf("My children are: %d and %d\n\n", pid, pid2);
        }
        if (pid2 == 0)
        {
            printf("I'm the 2nd child\n My PID is: %d\n", getpid());
            printf("My PPID is: %d\n\n", getppid());        
        }
    }
    
    
}