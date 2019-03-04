#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

#define MAXFILS 3

int main(int argc, char **argv[]){
  int i,j;
  struct rusage r;
  printf("Début pére\n");
  
  j = 0;
  for(i = 2; i < argc; i++){
    if(j++>=MAXFILS){
      printf("J'attends un fils\n");
      j = 0;
      wait(NULL);
    }
    if(fork()==0){
      wait3(NULL,0,&r);
      printf("Fils %d: %f\n",i,r.ru_utime.tv_sec);
      execlp("grep","grep","--color",argv[1],argv[i],NULL);
    }
  }
  for(i=2; i < argc; i++)
    wait(NULL);

  wait3(NULL,0,&r);
  printf("Père: %f\n",r.ru_utime.tv_sec);
  
  printf("Fin père\n");
  return 0;
}
    
