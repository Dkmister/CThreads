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
  int t4 = ccreate((void*)&funct3, NULL, 1);
  int t5 = ccreate((void*)&funct3, NULL, 1);

  cjoin(t2);

  printf("\nFim\n");
}
