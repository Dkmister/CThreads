#include "../include/cthread.h"
#include <stdio.h>

void funct1(){
  printf("função 1 chamada!");
}

void funct2(){
  printf("função 2 chamada!");
}

void funct3(){
  printf("função 3 chamada!");
}

int main(){
  printf("Começando");

  int t1 = ccreate(funct1, NULL, 0);
  int t2 = ccreate(funct2, NULL, 2);
  int t3 = ccreate(funct3, NULL, 1);

  cjoin(t2);

  printf("\nFim\n");
}
