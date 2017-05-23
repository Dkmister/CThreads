#include "../include/execution_queue.h"
#include "../include/ready_queue.h"
#include "../include/short_scheduler.h"
#include "../include/semaphore.h"
#include <ucontext.h>
#include <stdlib.h>
#define STACK_SIZE 4096


/* escalonador de longo prazo vai usar as seguintes filas:

  - ready queue

*/
ucontext_t * threadEndContext = NULL;

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
  releaseThread(currentThread->tid);
  executeNextThread();
}

void initLongScheduler(){
  threadEndContext = malloc(sizeof(ucontext_t));
  getcontext(threadEndContext);
  char endThreadStack[STACK_SIZE];
  threadEndContext->uc_stack.ss_sp = endThreadStack;
  threadEndContext->uc_stack.ss_size = sizeof(endThreadStack);
  threadEndContext->uc_link = NULL;
  makecontext(threadEndContext, endThread, 0);

  TCB_t * mainThread = malloc(sizeof(TCB_t));
  mainThread->tid = newTid();
  mainThread->ticket = 0;
  ucontext_t * mainContext;
  mainContext = malloc(sizeof(ucontext_t));
  getcontext(mainContext);
  char stack[STACK_SIZE];
  mainContext->uc_stack.ss_sp = stack;
  mainContext->uc_stack.ss_size = sizeof(stack);
  mainContext->uc_link = threadEndContext;
  mainThread->context = *(mainContext);
  addThreadToExecutionQueue(mainThread);
}

int createNewThread(void* (*context)(void*), int prio){
  ucontext_t * thisNewContext = malloc(sizeof(ucontext_t));
  getcontext(thisNewContext);
  thisNewContext->uc_link = threadEndContext;
  char stack[STACK_SIZE];
  thisNewContext->uc_stack.ss_sp = stack;
  thisNewContext->uc_stack.ss_size = sizeof(stack);
  makecontext(thisNewContext, (void*)context, 0);

  TCB_t * newThread = malloc(sizeof(TCB_t));
  newThread->context = (*thisNewContext);
  newThread->tid = newTid();
  newThread->ticket = prio;
  addThreadToReadyQueue(newThread);
  return newThread->tid;
}
