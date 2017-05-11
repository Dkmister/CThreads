#include "../../include/cdata.h"
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>

void funcaoContext(){
  printf("\nSou a função de teste para contextos!\n");
}

void terminoFuncaoContext(){
  printf("\nTerminei de executar a função de teste de contextos!");
}

TCB_t * removeThreadFromReadyQueue(int tid){
  return malloc(sizeof(TCB_t));
}

int addThreadToReadyQueue(TCB_t * thread){
  return 0;
}

TCB_t * getNextThreadToExecute(){
  char stack[8192];
  printf("Retornando a próxima thread");
  TCB_t * thread = malloc(sizeof(TCB_t));
  ucontext_t * context = malloc(sizeof(ucontext_t));
  getcontext(context);
  context->uc_stack.ss_sp = stack;
  context->uc_stack.ss_size = sizeof stack;
  context->uc_link = terminoFuncaoContext;
  makecontext(context, funcaoContext, 0);
  thread->context = *context;
  thread->tid = 0;
  return thread;
}
