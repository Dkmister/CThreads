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

ucontext_t newContext(void * context){
  ucontext_t thisNewContext;
  getcontext(&thisNewContext);
  char stack[256];
  thisNewContext.uc_stack.ss_sp = stack;
  thisNewContext.uc_stack.ss_size = sizeof(stack);
  thisNewContext.uc_link = NULL;
  makecontext(&thisNewContext, context, 0);
  return thisNewContext;
}

ucontext_t endContext(){
}

int createNewThread(void * context, int prio){
  if(firstThread == 0){
    createMainThread();
  }
  TCB_t * newThread = malloc(sizeof(TCB_t));
  newThread->tid = newTid();
  newThread->context = newContext(context);
  addThreadToReadyQueue(newThread);
  return newThread->tid;
}

void createMainThread(){
  TCB_t * mainThread = malloc(sizeof(TCB_t));
  mainThread->tid = newTid();
  ucontext_t mainContext;
  getcontext(&mainContext);
  char stack[256];
  mainContext.uc_stack.ss_sp = stack;
  mainContext.uc_stack.ss_size = sizeof(stack);
  mainContext.uc_link = NULL;
  addThreadToExecutionQueue(mainThread);
}
