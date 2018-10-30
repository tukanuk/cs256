#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char buf[20] ="Today is a New day.";
  int i=0;
  while(1){
   fputc(buf[i], stdout);
   i = (i+1) % 20;      // i will not exceed 19
  usleep(10); // sleep one second
  } 
}
