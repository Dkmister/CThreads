#include "../include/cthread.h"
#include "../include/support.h"
#include "../include/execution_queue.h"
#include "../include/short_scheduler.h"
#include "../include/medium_scheduler.h"
#include "../include/long_scheduler.h"
#include "../include/errors.h"
#include <stdlib.h>

PFILA2 threadSemaphores = NULL;

void initializeSemaphores(){
  threadSemaphores = malloc(sizeof(FILA2));
  CreateFila2(threadSemaphores);
}

typedef struct ThreadSemaphore {
  int threadTid;
  csem_t * semaphore;
} ThreadSemaphore;

csem_t * searchThreadSemaphore(int tid){
  if(FirstFila2(threadSemaphores) == ERROR){
    return NULL; //Se a fila não estiver vazia
  }
  do{ //Itera na fila até achar o semáforo
    ThreadSemaphore * thSemaphore;
    thSemaphore = GetAtIteratorFila2(threadSemaphores);
    if(thSemaphore!=NULL && thSemaphore->threadTid == tid){ //Se achou a estrutura da thread
      return thSemaphore->semaphore; //Se achar, retorna o semaforo
    }
  }while(NextFila2(threadSemaphores) == 0);
  return NULL; //Se não achou nada, retorna null
}

int newSemaphore(csem_t * semaphore, int maxThreadsOnResource){
  semaphore->count = maxThreadsOnResource; //inicializa o contador do semáforo
  PFILA2 fila = malloc(sizeof(FILA2));
  if(CreateFila2(fila) == ERROR){ //inicializa uma fila
    return ERROR;
  }
  semaphore->fila = fila;
  return SUCCESS;
}

int waitOnSemaphore(csem_t * semaphore){
  if(semaphore->count > 0){ //Se o semáforo ainda puder ser decrementado (recurso pode ser alocado)
    semaphore->count = semaphore->count - 1; //Decrementa o contador do semáforo
  } else { //Se o semáforo ja estiver ocupado (recurso não pode mais ser alocado)
    TCB_t * currentThread = getCurrentThread(); //pega a thread atualmente em execução
    if(AppendFila2(semaphore->fila, currentThread) == ERROR){ //Coloca a thread na fila de espera do semáforo
      return ERROR;
    }
    BlockCurrentThread(); //Bloqueia a thread atual e executa a próxima
  }
  return SUCCESS;
}

int waitOnThread(int tid){
  int threadHasFinished = finishedThread(tid);
  csem_t * semaphore = searchThreadSemaphore(tid);
  if(semaphore == NULL &&  threadHasFinished != SUCCESS){ //Procura a estrutura de semáforo referente à thread referenciada por tid;
    semaphore = malloc(sizeof(csem_t));
    newSemaphore(semaphore, 0); //Se não achar nenhuma fila de espera na thread, cria um novo semáforo e nova instancia de fila de espera
    ThreadSemaphore * thSemaphore = malloc(sizeof(ThreadSemaphore));
    thSemaphore->semaphore = semaphore;
    thSemaphore->threadTid = tid;
    if(AppendFila2(threadSemaphores, thSemaphore) == ERROR){
      return ERROR;
    }
    waitOnSemaphore(semaphore);
    return SUCCESS; //Retorna sucesso
  } else {
    return ERROR;
  }
}

int releaseSemaphore(csem_t * semaphore){
  semaphore->count = semaphore->count + 1; //Incrementa o valor do semaforo
  if(LastFila2(semaphore->fila) != ERROR){ //Caso tenha alguma thread esperando
    TCB_t * waitingThread = (TCB_t *)GetAtIteratorFila2(semaphore->fila);
    semaphore->count = semaphore->count - 1;
    UnblockThread(waitingThread->tid);
    DeleteAtIteratorFila2(semaphore->fila);
  }
  return SUCCESS;
}

int releaseThread(int tid){
  csem_t * semaphore = searchThreadSemaphore(tid);
  if(semaphore == NULL){ //Procura a thread na fila de semáforos
    return ERROR;
  }
  if(FirstFila2(semaphore->fila) == ERROR){
    return ERROR;
  }
  TCB_t * thread = (TCB_t *)GetAtIteratorFila2(semaphore->fila);
  UnblockThread(thread->tid); //Desbloquear (adicionar à fila de aptos)
  return SUCCESS;
}
