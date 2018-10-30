#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
   int fd;
   int status;
   
   if ( (fd = open("file.txt", O_RDONLY)) == -1)
    {
        perror("file opening problem ");
        exit(1);
    }

    int pid = fork();
    wait(&status);

    if (pid)
    {
        printf("\nMy child has terminated. Status %d\n\n", WEXITSTATUS(status));
        exit(1);
    }

    if (!pid)
    {
        char buff[255];
        long n;
        while ( (n=read(fd, buff, 255)) > 0)
        {
            write(STDIN_FILENO, buff, n);
        }
        sleep(5);
        exit(20);
    }    
}