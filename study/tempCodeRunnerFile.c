#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void myAlarmHandler()
{
  printf("I got an alarm, I took care of it\n");
  alarm(3);
}
int main(int argc, char *argv[])
{
  signal(SIGALRM, myAlarmHandler); //install handler
  alarm(3);
  while (1)
  {
    printf("I am working\n");
    sleep(1);
  }
}