#include "../include/execution_queue.h"
#include "../include/ready_queue.h"
#include <ucontext.h>


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
  TCB_t currentThread = removeThreadFromExecutionQueue();
  releaseThread(currentThread->tid);
  free(currentThread);
  executeNextThread();
}

void createNewThread((void*) context, int prio){
  TCB_t * newThread = malloc(sizeof(TCB_t));
  newThread->tid = newTid();
  thread.context = newContext(context);
  addThreadToReadyQueue(thread);
}

ucontext_t newContext((void*)context){
  ucontext_t thisNewContext;
  getcontext(&thisNewContext);
  makecontext(&thisNewContext, context);
  char stack[256]
  thisNewContext.stack.ss_sp = stack;
  thisNewContext.stack.ss_size = sizeof(stack);
  thisNewContext.uc_link = endThread;
  return thisNewContext;
}
