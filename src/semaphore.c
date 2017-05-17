#include "../include/cthread.h"
#include "../include/support.h"
#include "../include/execution_queue.h"
#include "../include/short_scheduler.h"
// #include "../include/.medium_term_scheduler.h"

PFILA2 threadSemaphores = NULL;

struct

int newSemaphore(csem_t * semaphore, int maxThreadsOnResource){
  PFILA2 fila;
  CreateFila2(fila);
  csem_t newSemaphore = malloc(sizeof(csem_t));
  newSemaphore->count = maxThreadsOnResource;
  newSemaphore->fila = fila;
  return semaphore;
}

int waitOnSemaphore(csem_t * semaphore){
  if(semaphore->count > 0){
    semaphore->count = semaphore->count - 1;
  } else {
    TCB_t * currentThread = getCurrentThread();
    AppendFila2(semaphore->fila, (void*)currentThread);
    BlockCurrentThread();
  }
}

int releaseSemaphore(csem_t semaphore){
  semaphore->count = semaphore->count + 1;
  if(LastFila2(semaphore->fila)){
    TCB_t * waitingThread = (TCB_t *)GetAtIteratorFila2(semaphore->fila); //Testar por erro
    semaphore->count = semaphore->count - 1;
    UnblockThread(waitingThread->tid);
    DeleteAtIteratorFila2(fila); //Testar por erro
  }
}

int waitOnThread(int tid){
  if(!threadSemaphores){
    CreateFila2(threadSemaphores);
  }
}

int releaseThread(int tid){

}

csem_t * searchThreadSemaphore(int tid){
  if(FirstFila2(threadSemaphores)){
    do{

    }while(NextFila2(threadSemaphores))
  }
}
