#include "../include/execution_queue.h"
#include "../include/ready_queue.h"
#include "../include/short_scheduler.h"
#include "../include/semaphore.h"
#include <ucontext.h>
#include <stdlib.h>


/* escalonador de longo prazo vai usar as seguintes filas:

  - ready queue

*/

int firstThread = 0;

int Tid = 0;

int newTid()
{
  int currentTid = Tid;
  Tid++;
  return currentTid;
}

void endThread(){
  TCB_t * currentThread = removeThreadFromExecutionQueue();
  releaseThread(currentThread->tid);
  free(currentThread);
  executeNextThread();
}

int createNewThread(void* (*context)(void*), int prio){
  if(firstThread == 0){
    createMainThread();
    firstThread = 1;
  }
  TCB_t * newThread = malloc(sizeof(TCB_t));
  
  ucontext_t * thisNewContext = malloc(sizeof(ucontext_t));
  getcontext(thisNewContext);
  char stack[8192];
  thisNewContext->uc_stack.ss_sp = stack;
  thisNewContext->uc_stack.ss_size = sizeof(stack);
  thisNewContext->uc_link = NULL;
  makecontext(thisNewContext, context, 0);
  newThread->context = (*thisNewContext);

  newThread->tid = newTid();
  addThreadToReadyQueue(newThread);
  return newThread->tid;
}

void createMainThread(){
  TCB_t * mainThread = malloc(sizeof(TCB_t));
  mainThread->tid = newTid();
  mainThread->ticket = 0;
  ucontext_t * mainContext;
  mainContext = malloc(sizeof(ucontext_t));
  getcontext(mainContext);
  char stack[8192];
  mainContext->uc_stack.ss_sp = stack;
  mainContext->uc_stack.ss_size = sizeof(stack);
  mainContext->uc_link = NULL;
  mainThread->context = *(mainContext);
  addThreadToExecutionQueue(mainThread);
}
