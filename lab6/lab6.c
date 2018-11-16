#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    double v1, v2;
    char operator;
    FILE* fp;

    if(fork() )
    {
        while (1)
        {
            while ( (fp = fopen("temp.txt", "r")) )
            {
                fclose(fp);
                sleep(1);
            }
            printf("input: ");
            scanf("%lf %lf %c", &v1, &v2, &operator);
            fp = fopen("temp.txt", "w");
            fprintf(fp, "%lf %lf %c\n", v1, v2, operator);
            fclose(fp);
            sleep(3);
        }
    }
    else
    {
        while (1)
        {
            if( (fp = fopen("temp.txt", "r")) )
            {
                fscanf(fp, "%lf %lf %c", &v1, &v2, &operator);
                fclose(fp);
                unlink("temp.txt");
                
                double result;
                switch (operator)
                {
                    case '+':
                        result = v1 + v2;
                        break;
                    case '-':
                        result = v1 - v2;
                        break;
                    case '/':
                        result = v1 / v2;
                        break;
                    case '*':
                        result = v1 * v2;
                        break;
                    default:
                        break;
                }
                printf("The result is: %lf\n", result);
                sleep(1);
            }
            else
            {
                while(!(fp=fopen("temp.txt", "r")))
                    sleep(1);
            }
        }
    }


}