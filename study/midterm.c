#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void CTR_handler()
{
  printf("Process %d got a CTR-C, exit\n", getpid());
  exit(2);
}
int main(int argc, char *argv[])
{
  int i;
  printf("First process, PID=%d, PPID=%d, PGID=%d\n",
         getpid(), getppid(), getpgid(0));
  signal(SIGINT, CTR_handler);
  for (i = 1; i <= 3; i++)
    fork();
  printf("PID=%d PGID=%d\n", getpid(), getpgid(0));
  pause();
}