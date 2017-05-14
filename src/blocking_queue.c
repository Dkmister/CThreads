#include "../include/cdata.h"
#include <stdlib.h>
#include <stddef.h>

TCB_t * currentThreadOnExecution;

// Funcao que adiciona thread na fila de bloqueados
// Retorna -1 caso haja erro, 0 se der tudo certo.
int AddThreadToBlockingQueue(TCB_t * thread)
{
  if(currentThreadOnExecution != NULL)
  {
    return -1;
  }
  currentThreadOnExecution = thread;
  return 0;
}


TCB_t * RemoveThreadFromBlockingQueue(int tid)
{
  TCB_t * thread = currentThreadOnExecution;

  currentThreadOnExecution = findreferencedThread(tid);
  currentThreadOnExecution = NULL; //Remove a thread atual
  return thread; //Retorna a referencia da thread retirada
  /*
  if(thread->tid == tid){ 
    currentThreadOnExecution = NULL; //Remove a thread atual
    return thread; //Retorna a referencia da thread retirada
  }*/
}
