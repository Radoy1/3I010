/* Diffusion tampon 1 case */

  #include <stdio.h> 
  #include <unistd.h> 
  #include <stdlib.h> 
  #include <signal.h> 
  #include <libipc.h>

/************************************************************/

/* definition des parametres */ 

  #define NE          2     /*  Nombre d'emetteurs         */ 
  #define NR          5     /*  Nombre de recepteurs       */ 

/************************************************************/

/* definition des semaphores */ 

	// A completer
#define EMET  0
#define MUTEX 6
int RECEP[NR] = {1,2,3,4,5};
        
/************************************************************/

/* definition de la memoire partagee */ 

	// A completer
typedef struct{
  int a;
  int nb_recep;
}t_segpart;

t_segpart *sp;

/************************************************************/

/* variables globales */ 
int emet_pid[NE], recep_pid[NR];

/************************************************************/

/* traitement de Ctrl-C */ 

  void handle_sigint(int sig) { 
      int i;
      for (i = 0; i < NE; i++) kill(emet_pid[i], SIGKILL); 
      for (i = 0; i < NR; i++) kill(recep_pid[i], SIGKILL); 
      det_sem(); 
      det_shm((char *)sp); 
  } 

/************************************************************/

/* fonction EMETTEUR */ 

	// A completer - contient les instructions executees
        // par un emetteur
void emetteur(int i){

  while(1){
    P(EMET);
    sleep(3);
    sp->a++;
    for (int j = 0; j < NR; j++)
      V(RECEP[j]);
    printf("Emetteur %d a fini d'ecrire\n",i);
  }
  
}

/************************************************************/

/* fonction RECEPTEUR */ 

	// A completer - contient les instructions executees
        // par un recepteur
void recepteur(int i){

  while(1){
    P(RECEP[i]);
    printf("Recepteur %d lit %d\n",i,sp->a);
    P(MUTEX);
    sp->nb_recep++;
    if(sp->nb_recep == NR){
      V(EMET);
      sp->nb_recep = 0;
    }
    V(MUTEX);
  }
  
}
/************************************************************/

int main() { 
    struct sigaction action;
    /* autres variables (a completer) */
    
    setbuf(stdout, NULL);
    int pid;

/* Creation du segment de memoire partagee */

	// A completer
    if( (sp = (t_segpart *) init_shm(sizeof(t_segpart))) == NULL){
      perror("init shm");
      exit(1);
    }
    sp -> a = 0;

/* creation des semaphores */ 

	// A completer
    if( creer_sem(NR+2) == -1){
      perror("creer sem");
      exit(1);
    }

/* initialisation des semaphores */ 

	// A completer
    init_un_sem(EMET,1);
    for(int i = 0; i < NR; i++)
      init_un_sem(RECEP[i],0);
    init_un_sem(MUTEX,1);
    
/* creation des processus emetteurs */ 

	// A completer - les pid des processus crees doivent
        // etre stockes dans le tableau emet_pid
    for(int i = 0; i < NE ; i++){
      if((pid=fork()) == -1){
	perror("fork");
	exit(1);
      }
      if(pid==0)
	emetteur(i);
    }
/* creation des processus recepteurs */ 

	// A completer - les pid des processus crees doivent
        // etre stockes dans le tableau recep_pid
    for(int i = 0; i < NR ; i++){
      if((pid=fork()) == -1){
	perror("fork");
	exit(1);
      }
      if(pid==0)
	recepteur(i);
    }
/* redefinition du traitement de Ctrl-C pour arreter le programme */ 

    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handle_sigint;
    sigaction(SIGINT, &action, 0); 
    
    pause();                    /* attente du Ctrl-C  */
    return EXIT_SUCCESS;
} 
