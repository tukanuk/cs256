#include <fcntl.h>
#include <stdio.h> // This is the server
#include <unistd.h>
#include <stdlib.h>
#include <sys/signal.h>
// #include <sys/signal.h>
#include <stdlib.h>


#include <fcntl.h>          // This is the client
#include <stdio.h>
int main(int argc, char *argv[]){
  int fd;
char ch;
  while((fd=open("/tmp/server", O_WRONLY))==-1){
    fprintf(stderr, "trying to connect\n");
    sleep(1);
}
  printf("Connected: type in data to be sent\n");
  while((ch=getchar()) != -1) // -1 is CTR-D
    write(fd, &ch, 1);
close(fd); }