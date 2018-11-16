#include <stdio.h>

int main()
{
    int int1 = 1;
    int int2 = 2;
    char operator = '+';
    int result = 3;
    char writebuff[50];

    sprintf(writebuff, "%d %c %d = %d", int1, operator, int2, result);

    printf("%sMORE\n", writebuff);

    return 0;
}