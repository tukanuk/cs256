#include <fcntl.h>
#include <stdio.h> // This is the server
#include <unistd.h>
#include <stdlib.h>
#include <sys/signal.h>
// #include <sys/signal.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd;
    char ch;
    unlink("/tmp/server"); // delete it if it exists
    if (mkfifo("/tmp/server", 0777) != 0)
        exit(1);
    // chmod("/tmp/server", 0777);
    while (1)
    {
        fprintf(stderr, "Waiting for a client\n");
        fd = open("/tmp/server", O_RDONLY);
        fprintf(stderr, "Got a client: ");
        while (read(fd, &ch, 1) == 1)
            fprintf(stderr, "%c", ch);
    }
}