#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void copyFiles(FILE *, FILE *);
int main(int argc, char *argv[]){
  FILE *f1, *f2;
  f1=fopen(argv[1], "r");
  if( f1 == NULL){
    perror("main function");
exit(1); }
  f2=fopen(argv[2], "w");
  if( f2 == NULL){
    perror("main function");
exit(2); }
  copyFiles(f1, f2);
exit(0); }

void copyFiles(FILE *f1, FILE *f2){
  int c;
  while((c=fgetc(f1)) != EOF)
    if (fputc(c, f2) == EOF){
      perror("copy function");
exit(3); }
  if(ferror(f1)){
    perror("copy function");
    exit(4);
} }