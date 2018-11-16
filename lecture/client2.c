#include <fcntl.h>
#include <stdio.h> // This is the server
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{ // Client
    char ch, fifoName[50];
    int fd;
    pid_t pid;
    while ((fd = open("/tmp/server", O_WRONLY)) == -1)
    {
        fprintf(stderr, "trying to connect\n");
        sleep(1);
    }
    
    pid = getpid();
    write(fd, &pid, sizeof(pid_t));
    close(fd);

    sprintf(fifoName, "/tmp/fifo%ld", pid);
    sleep(1);
    
    fd = open(fifoName, O_RDONLY);
    while (read(fd, &ch, 1) == 1)
        fprintf(stderr, "%c", ch);
    close(fd);
}
