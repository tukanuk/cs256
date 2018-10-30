#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
   char line[255];
   int status=0;

    while(1)
    {
        fgets(line, 255, stdin);
        if(!pid())
        {
            execlp(line, line, NULL);
        }
        wait(&status);
    }
}