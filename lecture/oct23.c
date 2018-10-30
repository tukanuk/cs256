#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    int status=0;

    execlp(argv[1], argv[1], argv[2], NULL);

    printf("I am still around\n");
}