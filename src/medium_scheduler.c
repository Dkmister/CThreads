// Localizar em  Cthreads/src/

#include "../include/cdata.h"
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
  TCB_t * currentThread = removeFirstThreadFromExecutionQueue();
  addThreadtoBlockingQueue(currentThread);
  getcontext(&currentThread->context);
  if(currentThread == NULL){
    return 0;
  }
  setcontext(&currentThread->context);
  return 1;

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
  TCB_t * firstThread = removeThreadFromBlockingQueue(tid);
  addThreadtoReadyQueue(firstThread);
  getcontext(&firstThread->context);
  if(firstThread == NULL){
    return 0;
  }
  setcontext(&firstThread->context);
  return 1;
}
