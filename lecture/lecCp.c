#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 int fd1, fd2;
 char buffer[100];
 long int n1;
 if(((fd1 = open(argv[1], O_RDONLY)) == -1) ||
    ((fd2 = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC,
                 0700)) == -1)){
    perror("file problem ");
exit(1); }
 while((n1=read(fd1, buffer, 100)) > 0)
   if(write(fd2, buffer, n1) != n1){
      perror("writing problem ");
exit(3); }
// Case of an error exit from the loop
 if(n1 == -1){
   perror("Reading problem ");
   exit(2);
 }
 close(fd2);
 exit(0);
}
