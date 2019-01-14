#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int readInt(int *value)
{
    char *buf[10];
    int i = 0, j, n, sign = 1;
    
    if ((n = read(0, buf, 10)) <= 0) // a fail read
        return (0);

    if (buf[0] == '-' || buf[0] == '+') // advance if sign is present
        i++;
    if (buf[0] == '-')
        sign = -1;
    *value = 0;
    printf("i: %d\n", i);
    for (j = i; j < (n - 1); j++)
        // do not consider ’\n’
        if (buf[j] >= '0' && buf[j] <= '9')
            *value = *value * 10 + (buf[j] - '0');
        else
            return (0);
    *value *= sign;
    return (1);
}

int main()
{
    int value;
    int sucess;

    sucess = readInt(&value);
    printf("%d\n%d\n", sucess, value);
}
// an illegal  nondigit charcater
// make it negative if sign = ’-’