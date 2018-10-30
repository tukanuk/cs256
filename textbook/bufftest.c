#include <stdio.h> // Example of buffering effect
#include <unistd.h>// This is needed for sleep()
int main(void){    // without fflush
  int i=0;
  char line[100]="Hello, my name No-Name\n";
  while(line[i] != NULL){
    putchar(line[i++]);
sleep(1); }
}
