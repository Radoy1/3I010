#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <sys/time.h>

void lance_commande(char *commande){
  struct timeval tv1;
  struct timeval tv2;
  struct tms t1,t2;
  int tdebut = gettimeofday(&tv1,NULL);
  tdebut = tv1.tv_sec;
  times(&t1);
  system(commande);
  times(&t2);
  int tfin = gettimeofday(&tv2,NULL);
  tfin =tv2.tv_sec;
  
  printf("Statistique de %s\n", commande);
  printf("Temps tot : %d\n", tfin-tdebut);
  printf("Temps user : %f\n",(float)(t2.tms_utime-t1.tms_utime)/(float)sysconf(_SC_CLK_TCK) );
  printf("Temps syst : %f\n",(float)(t2.tms_stime-t1.tms_stime)/(float)sysconf(_SC_CLK_TCK));
  printf("Temps user fiston : %f\n", (float)(t2.tms_cutime-t1.tms_cutime)/(float)sysconf(_SC_CLK_TCK));
  printf("Temps syst fils : %f\n",(float)(t2.tms_cstime-t1.tms_cstime)/(float)sysconf(_SC_CLK_TCK));
}
int main(int argc,char **argv){
  int i;

  for(i=1;i<argc;i++)
    lance_commande(argv[i]);
  
  return 0;
}
