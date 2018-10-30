/*
   Name:		ass2.c
   Purpose:	Assignment 2        
   Author:  Ben Davidson
            104924033
   Date:    1015-2018 3:47p
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int readLine(int fd, char *buff, int size);
int fd2;
int validateSINBuffer(int i, char *buff);

int main (int argc, char *argv[] )
{
    int fd1;            // file 
    char buffer[100];   // 100 char buffer
    long int n1;
    int code[9] = {1,2,1,2,1,2,1,2,1};

    if ( (fd1 = open(argv[1], O_RDONLY)) == -1)
    {
        perror("source file problem ");
        exit(1);
    }
    if ( (fd2 = open(argv[2], O_CREAT|O_WRONLY, 0700)) ==-1)
    {
        perror("destination file problem");
        exit(1);
    }

    while(1)
    {
        int i;
        if ( (i = readLine(fd1, buffer, 100)) < 1)
        {
            printf ("exit code %d \n", i);
            exit(1);
        }

        //printf("return: %d contents of buffer: \'%s\'\n", i, buffer);

        // if there are spaces and nothing else beyond nine digits, accept.
        //printf("Length good: %d\n", validateSINBuffer(i, buffer));

        if (validateSINBuffer(i, buffer))
        {
            int tmp;
            for (int i; i < 8; i++)
            {
                buffer[i] = buffer[i] * code[i]; 
                if (buffer[i] > 9)
                {
                    buffer[i] = 1 + i%10;
                }
            }

            for (int i; i < 8 ; i++)
            {
                tmp += buffer[i];
            }

            // output the sin number
            write(STDIN_FILENO, buffer, 20);
            if (tmp%10 == 0)
            {    
                char message[10] = " VALID\n";
                write(STDIN_FILENO, message, 10);
            }
            else
            {
                char message[11] = " NOT VALID\n";
                write(STDIN_FILENO, message, 11);
            }
        }

        

    }

    close(fd1);
    exit(0);
}

int readLine(int fd, char *buff, int size)
{
    char tmp[1];
    int buffPos=0;
    long int n2;
    memset(buff, 0, strlen(buff));
    while( (n2=read(fd, tmp, 1)) > 0 )
    {
        if (*tmp == '\n') 
        {
            // printf("end of line reached.\n");
            break;
        }
        // printf("buff: %c\n", buff[0]);
        buff[buffPos++] = *tmp;
    }

    // error in reading
    if (n2 == -1)
    {
        perror("read line problem");
        return -1;
    }

    // buff check
    for (int j=0 ; j < buffPos; j++)
    {
        // printf("P%d: %c\n", j, buff[j]);
    }
    // printf("Whole buffer check: %s.\n", buff);

    // end of file
    if (n2 == 0)
    {
        return 0;
    }
    
    // return number of bytes read
    return buffPos;
}

int validateSINBuffer(int i, char *buff)
{
    if (i > 8)
    {
        for (int extraCheck = 9; extraCheck < i ; extraCheck++)
        {
            if (buff[extraCheck] != ' ') return -1;
        }
    }
    return 1; 
}