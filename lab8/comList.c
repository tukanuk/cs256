#include <stdio.h>
#include <string.h>

int main (int argc, char * argv[])
{
    char * parse[20];
    char * input = argv[1];
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
        printf("%d command: %s\n", i, parse[i]);
        i++;

    }
    
    // printf("Second command: %s\n", parse[1]);
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