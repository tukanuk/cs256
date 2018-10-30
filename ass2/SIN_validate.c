/*
   Name:	ass2.c
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

#define DEBUG 0

int readLine(int fd, char *buff, int size);
int validateSINBuffer(int i, char *buff);

int main (int argc, char *argv[] )
{
    int fd1;                            // file 
    char buffer[100];                   // 100 char buffer
    long int n1;                        //  
    int endFile = 0;                    // marks end of file
    int code[9] = {1,2,1,2,1,2,1,2,1};  // values for validation

    // check the file
    if ( (fd1 = open(argv[1], O_RDONLY)) == -1)
    {
        perror("file opening problem ");
        exit(1);
    }
   
    while(1)
    {
        int lineStatus; // the return of readLine
        if ( (lineStatus = readLine(fd1, buffer, 100)) < 1)
        {
            if (lineStatus < 0)
            {
                printf ("error reading exit code %d \n", lineStatus);
                exit(1);
            }
            else if (lineStatus == 0) 
            {
                endFile = 1;
            }
        }

        if (validateSINBuffer(lineStatus, buffer))
        {
            int tmp=0; // multiplication result
            int sum=0; // running sum
            
            if (DEBUG) 
            {
                printf("Buffer: ");
                for (int i=0; i < 9 ; i++)
                {
                    printf("%c", buffer[i]);
                }
                printf("\n");
            }
            
            // performs the calcualtions on each digit and keep a running sum
            for (int i=0; i < 9; i++)
            {
                tmp = (buffer[i] - 48) * code[i]; 
                if (DEBUG) printf("math: %d = %d * %d\n", tmp, (buffer[i]-48), code[i]);
                if (tmp > 9)
                {
                    tmp = 1 + tmp%10;
                    if (DEBUG) printf("MOD %d ", tmp);
                }
                sum += tmp;
            }

            if (DEBUG) printf("Sum: %d\n", sum);
            

            // output the sin number
            if (strlen(buffer) < 10) buffer[9]=' '; // insert a formatting space if needed
            write(STDIN_FILENO, buffer, 10);
            if (sum%10 == 0)                        // final step of the formula
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
        // if the SIN was not sutiable to process (letters, too long or short)
        else
        {
           if (strlen(buffer) > 9) buffer[9]='*';   // if there are extra characters beyond 9 place a star to note they were there and perserve formatting
           write(STDIN_FILENO, buffer, 10);
           char message[15] = " NOT VALID\n";
           if (!endFile) write(STDIN_FILENO, message, 15);
        }

        if (endFile) 
        {
            char message[35] = "* line info shortened for display\n";
            write(STDIN_FILENO, message, 35);
            exit(0);        
        }

    }

    close(fd1);
    exit(0);
}

/* readLine
 * input: file, buffer, size of buffer
 * return: -1 error in reading, 0 end of file, >0 number of bytes read
 */
int readLine(int fd, char *buff, int size)
{
    char tmp[1];
    int buffPos=0;
    long int n2;
    memset(buff, 0, strlen(buff)); // clear the buffer for each line
    while( (n2=read(fd, tmp, 1)) > 0 )
    {
        if (*tmp == '\n') 
        {
            break;
        }
        buff[buffPos++] = *tmp;
    }

    // error in reading
    if (n2 == -1)
    {
        perror("read line problem");
        return -1;
    }

    // end of file
    if (n2 == 0)
    {
        return 0;
    }
    
    // return number of bytes read
    return buffPos;
}

/* validateSINBigger
 * input: length of line, buffer
 * return: 0 for invalid, 1 for valid
 */
int validateSINBuffer(int length, char *buff)
{
   if (DEBUG) printf("\nSIN:    %s\n", buff);

    // are there non digits?
    for (int j=0 ; j < 8; j++)
    {
        if (buff[j] < '0' || buff[j] > '9')
        {
            if (DEBUG) printf("NON DIGIT: %d, %c\n", buff[j], buff[j]);
            return 0;
        } 
    }

    // if longer then nine is there anything other than spaces?
    if (length > 9)
    {
        for (int extraCheck = 9; extraCheck < length ; extraCheck++)
        {
            if (buff[extraCheck] != ' ')
            {
                if (DEBUG) printf("NON SPACE AFTER NINE\n");
                return 0;
            } 
        }
    }
    return 1; 
}