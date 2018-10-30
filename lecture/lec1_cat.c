#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  FILE *fd;
  char c;
  if(argc==1)
    fd=stdin;
  else
   if((fd = fopen(argv[1], "r"))==NULL){
     fprintf(stderr,"Cannot open %s\n", argv[1]);
exit(0); }
  while( (c=getc(fd)) != EOF)
    putc(c, stdout);
exit(0); }
