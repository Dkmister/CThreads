#include "../include/cthread.h"
#include <stdio.h>

void funct1(){
  printf("\nfunção 1 chamada!\n");
}

void funct2(){
  printf("\nfunção 2 chamada!\n");
}

void funct3(){
  printf("\nfunção 3 chamada!\n");
}

int main(){
  printf("\nComeçando\n");

  int t1 = ccreate((void*)&funct1, NULL, 0);
  int t2 = ccreate((void*)&funct2, NULL, 3);
  int t3 = ccreate((void*)&funct3, NULL, 1);

  cjoin(t1);
  cyield();
  cjoin(t2);

  csem_t * semaforo = malloc(sizeof(csem_t));
  csem_init(semaforo, 2);
  printf("%d\n", semaforo->count);
  cwait(semaforo);
  cwait(semaforo);
  printf("%d\n", semaforo->count);
  cwait(semaforo);
  csignal(semaforo);
  csignal(semaforo);
  printf("%d\n", semaforo->count);
  cjoin(t3);


  char * names = malloc(512);
  cidentify(names, 512);
  printf("%s", names);

  printf("\nFim\n");
}
