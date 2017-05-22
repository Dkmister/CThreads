#include "../include/execution_queue.h"
#include "../include/ready_queue.h"
#include "../include/short_scheduler.h"
#include "../include/semaphore.h"
#include <ucontext.h>
#include <stdlib.h>


/* escalonador de longo prazo vai usar as seguintes filas:

  - ready queue

*/

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

ucontext_t newContext(void * context){
  ucontext_t thisNewContext;
  getcontext(&thisNewContext);
  makecontext(&thisNewContext, context, 0);
  char stack[256];
  thisNewContext.uc_stack.ss_sp = stack;
  thisNewContext.uc_stack.ss_size = sizeof(stack);
  thisNewContext.uc_link = (void*)endThread;
  return thisNewContext;
}

int createNewThread(void * context, int prio){
  TCB_t * newThread = malloc(sizeof(TCB_t));
  newThread->tid = newTid();
  newThread->context = newContext(context);
  addThreadToReadyQueue(newThread);
  return newThread->tid;
}
