#include "../include/execution_queue.h"
#include "../include/ready_queue.h"
#include "../include/short_scheduler.h"
#include "../include/semaphore.h"
#include "../include/errors.h"
#include <ucontext.h>
#include <stdlib.h>
#define STACK_SIZE 4096


/* escalonador de longo prazo vai usar as seguintes filas:

  - ready queue

*/
ucontext_t * threadEndContext = NULL;
PFILA2 endedThreads = NULL;

int Tid = 0;

int newTid()
{
  int currentTid = Tid;
  Tid++;
  return currentTid;
}


void endThread(){
  getcontext(threadEndContext);
  TCB_t * currentThread = removeThreadFromExecutionQueue();
  AppendFila2(endedThreads, currentThread);
  currentThread->state = 4;
  releaseThread(currentThread->tid);
  executeNextThread();
}

void initLongScheduler(){
  endedThreads = malloc(sizeof(FILA2));
  CreateFila2(endedThreads);

  threadEndContext = malloc(sizeof(ucontext_t));
  getcontext(threadEndContext);
  threadEndContext->uc_stack.ss_sp = (char*)malloc(SIGSTKSZ);
  threadEndContext->uc_stack.ss_size = SIGSTKSZ;
  threadEndContext->uc_link = NULL;
  makecontext(threadEndContext, endThread, 0);

  TCB_t * mainThread = malloc(sizeof(TCB_t));
  mainThread->tid = newTid();
  mainThread->ticket = 0;
  ucontext_t * mainContext;
  mainContext = malloc(sizeof(ucontext_t));
  getcontext(mainContext);
  mainContext->uc_stack.ss_sp = (char*)malloc(SIGSTKSZ);
  mainContext->uc_stack.ss_size = SIGSTKSZ;
  mainContext->uc_link = threadEndContext;
  mainThread->context = *(mainContext);
  addThreadToExecutionQueue(mainThread);
}

int finishedThread(int tid){
  if(FirstFila2(endedThreads) == ERROR){
    return ERROR; //Se a fila não estiver vazia
  }
  do{
    TCB_t * thread;
    thread = (TCB_t*)GetAtIteratorFila2(endedThreads);
    if(thread != NULL && thread->tid == tid){
      return SUCCESS;
    }
  }while(NextFila2(endedThreads) == 0);
  return ERROR;
}

int createNewThread(void* (*context)(void*), int prio){
  ucontext_t * thisNewContext = malloc(sizeof(ucontext_t));
  getcontext(thisNewContext);
  thisNewContext->uc_link = threadEndContext;
  thisNewContext->uc_stack.ss_sp = (char*)malloc(SIGSTKSZ);
  thisNewContext->uc_stack.ss_size = SIGSTKSZ;
  makecontext(thisNewContext, (void*)context, 0);

  TCB_t * newThread = malloc(sizeof(TCB_t));
  newThread->context = (*thisNewContext);
  newThread->tid = newTid();
  newThread->ticket = prio;
  addThreadToReadyQueue(newThread);
  return newThread->tid;
}
