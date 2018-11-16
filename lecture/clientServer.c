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

void child(pid_t client);
int main(int argc, char *argv[])
{
    int fd, status;
    char ch;
    pid_t pid;
    unlink("/tmp/server");
    if (mkfifo("/tmp/server", 0777))
    {
        perror("main");
        exit(1);
    }
    // chmod("/tmp/server", 0777);

    while (1)
    {
        fprintf(stderr, "Waiting for a client\n");
        fd = open("/tmp/server", O_RDONLY);
        fprintf(stderr, "Got a client: ");
        read(fd, &pid, sizeof(pid_t));
        fprintf(stderr, "%d\n", pid);
        if (fork() == 0)
        {
            close(fd);
            child(pid);
        }
        else
            waitpid(0, &status, WNOHANG);
    }
}

void child(pid_t pid)
{
    char fifoName[100];
    char newline ='\n';
    int fd, i;
    sprintf(fifoName, "/tmp/fifo%d", pid);
    mkfifo(fifoName, 0777);
    // chmod(fileName, 0777);
    fd = open(fifoName, O_WRONLY); 
    for (i = 0; i < 10; i++)
    {
        write(fd, fifoName, strlen(fifoName));
        write(fd, &newline, 1);
    }
    close(fd);
    unlink(fifoName);
    exit(0);
}