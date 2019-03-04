#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define L 3

int main(int argc, char **argv[]){
  int i, pid;
  for(i = 0; i < L; i++){
    pid = fork();
    if(pid!=0)
      pid = fork();
    if(pid!=0)
      break;
  }
  sleep(30);
  
}
