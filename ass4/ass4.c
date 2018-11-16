#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define DEBUG 0
#define LINELENGTH 255

void childFunction(char *line);

int main (int argc, char *argv[])
{
   int status; // exit codes
   
   char *writeBuff = "This program makes simple arithmetics\n\n";
   char readBuff[LINELENGTH];
   int length = strlen(writeBuff);
   write(STDIN_FILENO, writeBuff, length);

   while (1)
   {
      writeBuff = "Enter an arithmetic statement, e.g. 34 + 132 > ";
      length = strlen(writeBuff);
      write(0, writeBuff, length); 
      int n = read(0, readBuff, LINELENGTH);
      if (DEBUG) write(STDOUT_FILENO, readBuff, n);

      if ( fork() ) // >0 for parent
      {
         writeBuff = "Created a child to make your operations, waiting...\n";
         length = strlen(writeBuff);
         write(0, writeBuff, length);
         wait(&status);
         
         if (DEBUG)
         {
            int check = WEXITSTATUS(status);
            printf("STATUS CHECK: %d", check);
         }
         
         // check exit status
         switch(WEXITSTATUS(status) )
         {
            case 50:
               writeBuff = "Wrong Statement\n";
               write(STDERR_FILENO, writeBuff, strlen(writeBuff));
               break;
            case 100:
               writeBuff = "Division by zero\n";
               write(STDERR_FILENO, writeBuff, strlen(writeBuff));
               break;
            case 200:
               writeBuff = "Wrong operator\n";
               write(STDERR_FILENO, writeBuff, strlen(writeBuff));
               break;
            default:
               break;
         }
      }
      else 
      {
         childFunction(readBuff);
      }
      
   }
}

void childFunction(char *line)
{
   int result;

   char *writebuff="I am a child working for my parent\n";
   int length = strlen(writebuff);
   write (0, writebuff, length);

   int int1, int2;
   char operator;
   if ( (sscanf(line, "%d %c %d", &int1, &operator, &int2) != 3) )
      exit(50); // wrong statement (not int, char, int)

   if (DEBUG) printf("PARSE: %d %c %d\n", int1, operator, int2);

   switch (operator)
   {
      case '+':
         result = int1 + int2;
         break;
      case '-':
         result = int1 - int2;
         break;
      case '*':
         result = int1 * int2;
         break;
      case '/':
         if (int2 == 0)
            exit(100); // divide by zero error
         result = int1 / int2;
         break;
      default:
         exit (200); // wrong statement (couldn't parse operator)
         break;
   }

   if (DEBUG) printf("RESULT: %d\n", result);

   char answer[50];
   sprintf(answer, "The answer is %d %c %d = %d\n\n", int1, operator, int2, result);
   if (DEBUG) printf("TEST: %s\n", answer);
   length = strlen(answer);
   write(0, answer, strlen(answer) );
   
   exit(0); // everything went fine
}