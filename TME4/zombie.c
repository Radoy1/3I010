#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv[]){
  int valeur;
  if(fork()==0){
    exit(1);
  }
  else{
    sleep(10);
    WEXITSTATUS(valeur);
    printf("Zombie 1 retourne %d\n",valeur);
  }

  if(fork()==0)
    exit(2);
  else{
    sleep(10);
    WEXITSTATUS(valeur);
    printf("Zombie 2 retourne %d\n",valeur);
  }
  return 0;
}
