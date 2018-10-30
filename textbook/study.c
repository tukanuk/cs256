#include <stdio.h>
#include <unistd.h>

long int myFunc(char *fileName){
    long int i=-1;
    FILE *fp;
    if(fp=fopen(fileName,  "r"))
      while(1){
        i++;
        printf("%c", fgetc(fp) );
        if(feof(fp))
        break; 
    }
    return(i); 
}

int main (int argc, char *argv[])
{
    myFunc("test.bash");

    return 0;
}

