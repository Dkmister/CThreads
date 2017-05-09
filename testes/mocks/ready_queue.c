#include "../../include/cdata.h"
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>

void funcaoContext(){
  printf("\nSou a função de teste para contextos!\n");
}

TCB_t * removeThreadFromReadyQueue(int tid){
  return malloc(sizeof(TCB_t));
}

int addThreadToReadyQueue(TCB_t * thread){
  return 0;
}

TCB_t * getNextThreadToExecute(){
  TCB_t * thread = malloc(sizeof(TCB_t));
  ucontext_t * context = malloc(sizeof(ucontext_t));
  makecontext(context, (void*)funcaoContext, 0);
  thread->context = *context;
  thread->tid = 0;
  return thread;
}
