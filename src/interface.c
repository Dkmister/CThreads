#include <string.h>

#include "../include/cdata.h"
#include "../include/cthread.h"

#include "../include/errors.h"
#include "../include/semaphore.h"

#include "../include/ready_queue.h"
#include "../include/execution_queue.h"
#include "../include/blocking_queue.h"

#include "../include/short_scheduler.h"
#include "../include/medium_scheduler.h"
#include "../include/long_scheduler.h"

int ccreate (void* (*start)(void*), void *arg, int prio){
  return createNewThread(start, prio);
}

int csetprio(int tid, int prio){
  TCB_t * thread = removeThreadFromReadyQueue(tid); //Tenta encontrar a thread na fila de aptos;
  if(thread != NULL){ //Se achou a thread
    thread->ticket = prio; //Altera a prioridade
    addThreadToReadyQueue(thread); //Adiciona novamente à fila de aptos
    return SUCCESS;
  } else { //Se não encontrou a thread na fila de aptos
    thread = RemoveThreadFromBlockingQueue(tid); //Procura a thread na fila de bloqueados
    if(thread != NULL){ //Se achou na fila de bloqueados
      thread->ticket = prio; //seta a prioridade
      AddThreadToBlockingQueue(thread); //Adiciona novamente a fila de bloqueados
      return SUCCESS;
    } else {
      thread = getCurrentThread(); //Pega a thread atualmente em execução
      if(thread->tid == tid){ //Se for a thread que estamos procurando
        thread->ticket = prio; //Seta a prioridade
        return SUCCESS;
      }
    }
  }
  return ERROR; //Caso nada de certo, retorna erro
}

int cyield(void){
  return executeNextThread();
}

int cjoin(int tid){
  return waitOnThread(tid);
}

int csem_init(csem_t *sem, int count){
  return newSemaphore(sem, count);
}

int cwait(csem_t *sem){
  return waitOnSemaphore(sem);
}

int csignal(csem_t *sem){
  return releaseSemaphore(sem);
}

int cidentify (char *name, int size){
  strcpy(name, "231060 G. Tassinari\n242276 V. Neto\n205680 J. Nakamura\n\0");
  return SUCCESS;
}
