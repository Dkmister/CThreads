#include "../include/cdata.h"
#include "../include/errors.h"
#include "../include/short_scheduler.h"
#include "../include/ready_queue.h"
#include "../include/blocking_queue.h"
#include "../include/execution_queue.h"
#include <ucontext.h>
#include <stdlib.h>
#include <stddef.h>
/*
Escalonador de Medio Prazo usara as seguintes filas:

execution_queue
blocking_queue
ready_queue


*/
/*
int BlockCurrentThread():
Funcao que remove a thread atual da fila de execucao
E a coloca na fila de bloqueados

Existem dois casos:

1 - Se tiver uma thread na fila de executando
0 - Caso nao houver uma thread na fila de execucao


*/
int BlockCurrentThread()
{

  TCB_t * currentThread = removeThreadFromExecutionQueue();
  AddThreadToBlockingQueue(currentThread);
  int * isReturningContext = malloc(sizeof(int));
  *isReturningContext = 0 ;
  getcontext(&currentThread->context);
  if (*isReturningContext == 0 ) {
    executeNextThread();
  }
  return SUCCESS;
}
/*
void UnblockThread(int tid):

Funcao que retira a primeira thread da fila de bloqueados
E a coloca na fila de aptos

Existem dois casos:

1 - Se tiver uma thread na fila de bloqueados
0 - Caso nao houver uma thread na fila de bloqueio
*/

int UnblockThread(int tid)
{
  TCB_t * unblockedThread = RemoveThreadFromBlockingQueue(tid);
  if(unblockedThread == NULL){
    return ERROR;
  }
  addThreadToReadyQueue(unblockedThread);
  return SUCCESS;
}
