#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int fd;
    char ch;
    if (argc != 2)
        perror("Like this: ./fifoS /tmp/filename11 /tmp/filename22");
    
    if (fork () )
    {
        while ((fd = open(argv[1], O_WRONLY)) == -1)
        {
            fprintf(stderr, "trying to connect\n");
            sleep(1);
        }
        printf("Connected: type in data to be sent\n");
        while ((ch = getchar()) != -1) // -1 is CTR-D
            write(fd, &ch, 1);
        close(fd);
    } else
    {
        
    }
}