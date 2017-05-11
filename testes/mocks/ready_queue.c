#include "../../include/cdata.h"
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>

void funcaoContext(){
  printf("Esta função é executada pelo thread mock da fila de aptos!");
  exit(1);
}

TCB_t * createMockThread(){
  char stack[8192];
  TCB_t * thread = malloc(sizeof(TCB_t));
  ucontext_t * context = malloc(sizeof(ucontext_t));
  getcontext(context);
  context->uc_stack.ss_sp = stack;
  context->uc_stack.ss_size = sizeof(stack);
  context->uc_link = NULL;
  makecontext(context, funcaoContext, 0);
  thread->context = (*context);
  thread->tid = 1;
  return thread;
}

TCB_t * removeThreadFromReadyQueue(int tid){
  return createMockThread();
}

int addThreadToReadyQueue(TCB_t * thread){
  return 0;
}

TCB_t * getNextThreadToExecute(){
  return createMockThread();
}
