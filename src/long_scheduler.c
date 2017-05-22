#include "../include/execution_queue.h"
#include "../include/ready_queue.h"
#include "../include/short_scheduler.h"
#include "../include/semaphore.h"
#include <ucontext.h>
#include <stdlib.h>


/* escalonador de longo prazo vai usar as seguintes filas:

  - ready queue

*/
ucontext_t * threadEndContext = NULL;
int firstThread = 0;

int Tid = 0;

int newTid()
{
  int currentTid = Tid;
  Tid++;
  return currentTid;
}

void endThread(){
  getcontext(threadEndContext);
  printf("\nOla!!!\n");
  TCB_t * currentThread = removeThreadFromExecutionQueue();
  releaseThread(currentThread->tid);
  executeNextThread();
}

int createNewThread(void* (*context)(void*), int prio){
  if(firstThread == 0){
    createMainThread();
    firstThread = 1;
  }
  ucontext_t * thisNewContext = malloc(sizeof(ucontext_t));
  getcontext(thisNewContext);
  char stack[4096];
  thisNewContext->uc_stack.ss_sp = stack;
  thisNewContext->uc_stack.ss_size = sizeof(stack);
  thisNewContext->uc_link = threadEndContext;
  makecontext(thisNewContext, context, 0);

  TCB_t * newThread = malloc(sizeof(TCB_t));
  newThread->context = (*thisNewContext);
  newThread->tid = newTid();
  newThread->ticket = prio;
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
  char stack[4096];
  mainContext->uc_stack.ss_sp = stack;
  mainContext->uc_stack.ss_size = sizeof(stack);

  threadEndContext = malloc(sizeof(ucontext_t));
  getcontext(threadEndContext);
  char endThreadStack[4096];
  threadEndContext->uc_stack.ss_sp = endThreadStack;
  threadEndContext->uc_stack.ss_size = sizeof(endThreadStack);
  threadEndContext->uc_link = NULL;
  makecontext(threadEndContext, endThread, 0);

  mainContext->uc_link = threadEndContext;
  mainThread->context = *(mainContext);
  addThreadToExecutionQueue(mainThread);
}
