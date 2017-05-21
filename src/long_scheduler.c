#include "../include/long_scheduler.h"



/* escalonador de longo prazo vai usar as seguintes filas:

  - ready queue

*/

int Tid = 0;

int newTid()
{
  Tid = Tid + 1;
  
  return Tid;
}

void createNewThread((void*) context, int prio){
  TCB_t * newThread = malloc(sizeof(TCB_t));
  newThread->tid = newTid(); 
  ucontext_t threadContext;
  getcontext(&threadContext);
  makecontext(&threadContext, context);
  threadContext.uc_link = releaseThread(newThread->tid);
  char stack[256]
  threadContext.stack.ss_sp = stack;
  threadContext.stack.ss_size = sizeof(stack);
  newThread.context = threadContext;
  addThreadToReadyQueue(newThread);
}

