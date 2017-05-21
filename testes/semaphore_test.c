#include "../include/short_scheduler.h"
#include "../include/semaphore.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>

#define SEMAPHORE_COUNTER 1

//Ao ser executado, espera-se que o novo semáforo tenha como counter o valor 5
void testNewSemaphore(csem_t * semaphore){
  newSemaphore(semaphore, SEMAPHORE_COUNTER);
  printf("  Valor do contador : %d\n", semaphore->count);
}

//Ao ser executado, espera-se que o contador do semáforo seja descontado em 1
void testWaitOnSemaphore(csem_t * semaphore){
  printf("Esperando pelo semáforo!\n");
  waitOnSemaphore(semaphore);
  printf("  Valor do contador : %d\n", semaphore->count);
  printf("Esperando pelo semáforo!\n");
  waitOnSemaphore(semaphore);
  printf("  Valor do contador : %d\n", semaphore->count);
}

//Ao ser executado, espera-se que o contador do semáforo seja incrementado em 1
void testReleaseSemaphore(csem_t * semaphore){
  printf("Liberando o semáforo!\n");
  releaseSemaphore(semaphore);
  printf("  Valor do contador : %d\n", semaphore->count);
  printf("Liberando o semáforo!\n");
  releaseSemaphore(semaphore);
  printf("  Valor do contador : %d\n", semaphore->count);
}

int main(){
  printf("Iniciando teste de gerenciamento de semáforos\n");
  printf("Criando novo semáforo:\n");
  csem_t * semaphore = malloc(sizeof(csem_t));
  testNewSemaphore(semaphore);
  testWaitOnSemaphore(semaphore);
  testReleaseSemaphore(semaphore);
  printf("Teste de gerenciamento de semaforos OK!\n");
  printf("Iniciando teste para gerenciamento de semaforos sobre threads!\n");
  return 0;
}
