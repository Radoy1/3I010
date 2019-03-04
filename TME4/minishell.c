#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv[]){

  char *commande = (char *)malloc(50*sizeof(char));
  int attendre = 1;
  scanf("%[^\n]",commande);
  if(commande[strlen(commande)-1]=='&'){
    attendre = 0;
    commande[strlen(commande)-1] = '\0';
  }
  char *comm1 = strtok(commande," ");
  char *comm2 = strtok(NULL," ");
  char *comm3 = strtok(NULL," ");
  char *comm4 = strtok(NULL," ");
  if(fork()==0){    
    execlp(comm1,comm1,comm2,comm3);
  }else{
    if(attendre){
      printf("J'attends le fils\n");
      wait(NULL);
    }
  }

  return 0;
}
