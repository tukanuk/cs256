#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void myAlarmHandler(){}; // to avoid quiting
int main(int argc, char *argv[])
{
    pid_t pid;
    if ((pid = fork()) > 0)
    {
        printf("My child should wait until I am done\n");
        sleep(4);
        printf("Child, now you can do your job\n");
        kill(pid, SIGALRM); // let the child wake up
        sleep(3);
        printf("Parent Exiting\n");
    }
    else
    {
        printf("I have to wait for my parent\n");
        signal(SIGALRM, myAlarmHandler);
        pause();
        printf("OK, now I can do my job\n");
        sleep(2);
        printf("Child Exiting\n");
    }
    exit(0);
}
