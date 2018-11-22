#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int buildCommand (char *com, char *comArgcv[10]);   

int main (int argc, char * argv[])
{
    char * parse[20];
    char * input = argv[1];
    int status;
    printf("INPUT: %s\n", input);


    int i=0; // counter
    parse[i] = strtok(input, ";");
    while(parse[i])
    {
        // puts(token);
        i++;
        parse[i] = strtok(NULL, ";");
        // token = strtok(NULL, ";");
    }

    i=0;
    while (parse[i] )
    {
        printf("Command %d: %s\n", i, parse[i]);
        i++;

    }
    
    char *com1 = parse[0];
    char *com2 = parse[1];

    char* comArgv[10];

    printf("First Command is made up of:\n");
    buildCommand(com1, comArgv);
    
    if (!fork() )
    {
        execvp(comArgv[0], comArgv);
        exit(0);
    }
    
    wait(&status);
    printf("Second Command is made up of:\n");
    buildCommand(com2, comArgv);
    if (!fork() )
    {
        execvp(comArgv[0], comArgv);
        exit(0);
    }

    wait(&status);

}

int buildCommand (char *com, char *comArgv[10])
{
    int i=0;
    
    comArgv[i] = strtok(com, " ");
    printf("-> %s\n", comArgv[i]);
    while (comArgv[i])
    {
        i++;
        comArgv[i] = strtok(NULL, " ");
        printf("%s\n", comArgv[i]);
    }
    return 0;
}   


/* parseString
 * INPUT: string, array to store ints in
 * OUTPUT: array populated with int, returns number of elements
 */
// int parseString (char stringSeq[], long S[maxN])
// {
//     int i=0;
//     char * end;
//     char *p = strtok(stringSeq," ");          // tokenizes string by spaces
//     while(p != NULL)                          // stop at end of string
//     {
//         // S[i++] = strtol(p, &end, 10);         // convert each token to an long int
//         p = strtok(NULL, " ");                // move to next token
//     }
// }