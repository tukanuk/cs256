#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int fd, fd2;
    char ch;

    if (argc != 2)
        perror("Like this: ./fifoS /tmp/filename11 /tmp/filename22");
    
    unlink(argv[1]); // delete it if it exists
    unlink(argv[2]); // delete it if it exists

    if (fork() )
    {
        if (mkfifo(argv[1], 0777) != 0)
            exit(1);
        chmod(argv[1], 0777);
        while (1)
        {
            fprintf(stderr, "Waiting for a client\n");
            fd = open(argv[1], O_RDONLY);
            fprintf(stderr, "Got a client: ");
            while (read(fd, &ch, 1) == 1)
                fprintf(stderr, "%c", ch);
        }
    } else
    {
      while ((fd2 = open(argv[2], O_WRONLY)) == -1)
        {
            fprintf(stderr, "trying to connect\n");
            sleep(1);
        }
        printf("Connected: type in data to be sent\n");
        while ((ch = getchar()) != -1) // -1 is CTR-D
            write(fd, &ch, 1);
        close(fd);   
    }
    
}