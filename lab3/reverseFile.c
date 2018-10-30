#include <stdio.h>
#include <wchar.h>

int main (int argc, char *argv[])
{
    FILE *fd1, *fd2;
    int ch;
    int lc; // line counter
    
    // open the files and check for open errors
    fd1 = fopen(argv[1], "r");
    if (fd1 == NULL)
    {
        perror ("File could not be opened");
        return -1;
    }
    fd2 = fopen(argv[2], "w");
    if (fd2 == NULL)
    {
        perror ("File could not be opened");
        return -1;
    }

    // find the size of the file
    fseek(fd1, 0, SEEK_END);
    long size = ftell(fd1);
    fseek(fd1, 0, SEEK_SET); // back to the beginning
    printf("%ld\n", size);

    char buffer[size]; // create a buffer equal to the size of the file
    char dest[size]; // create a buffer equal to the size of the file

    // determine the number of lines in the file
    while (1)
    {
        ch = fgetc(fd1);
        if (ch == '\n')
        {
            lc++;
        }
        if (ch < 0) break;
    }

    printf("lines: %d\ncat: %s\n", lc, buffer);

    while (1)
    {
        fgets(dest,)
    }
    return 0;
} 