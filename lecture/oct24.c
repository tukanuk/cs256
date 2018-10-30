#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// int main(int argc, char *argv[])
// {
//   alarm(4);
//   while(1)
//   {
//     printf("Going to sleep\n");
//     sleep(1); 
//   }
  
//   printf("Exiting\n"); // will never get executed
//   exit(0); 
// }

// int main(int argc, char *argv[]){
//   int i;
//   void (*oldHandler1)(); //to save default handlers
//   void (*oldHandler2)(); //for CTR-C and CTR-Z
//   oldHandler1=signal(SIGINT, SIG_IGN);//ignore CTR-C
//   oldHandler2=signal(SIGTSTP, SIG_IGN);//ignore CTR-Z
//   for(i=1; i<=10; i++){
//     printf("I am not sensitive to CTR-C/CTR-Z\n");
// sleep(1); }
//   signal(SIGINT, oldHandler1);  // restore default
//   signal(SIGTSTP, oldHandler2); // restore default
//   for(i=1; i<=10; i++){
//     printf("I am sensitive to CTR-C/CTR-Z\n");
// sleep(1); }
// }

void AlarmHandler(){
  static int n = 0;
  if(n++ < 6 ){
    printf("Beeping%c%c%c\n", 7, 7, 7);
    alarm(10);
  }else
exit(0); }
int main(int argc, char *argv[]){
  signal(SIGALRM, AlarmHandler); //install a handler
  AlarmHandler();
  while(1) pause();
}

// void myAlarmHandler(){
//   printf("I got an alarm, I took care of it\n");
//   alarm(3);
// }
// int main(int argc, char *argv[]){
//   signal(SIGALRM, myAlarmHandler);//install handler
//   alarm(3);
//   while(1){
//     printf("I am working\n");
//     sleep(1);
// } 
// }