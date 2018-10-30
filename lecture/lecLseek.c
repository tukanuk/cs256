#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

//solution 2: start writing at end
int main(int argc, char *argv[]){
 int fd1, fd2;
 char buffer; // 1 character buffer
 long int i=0, fileSize=0;
 fd1=open(argv[1], O_RDONLY);
 fd2=open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0755);
 while(read(fd1, &buffer, 1)>0)
   fileSize++;
 lseek(fd2, fileSize-1, SEEK_SET);//pointer to end
 lseek(fd1, 0, SEEK_SET);
 while(++i <= fileSize){
   read(fd1, &buffer, 1);
   lseek(fd2, -i, SEEK_END);
   write(fd2, &buffer, 1);
 }
 close(fd1);
 close(fd2);
}
