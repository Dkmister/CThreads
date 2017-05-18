#include "../include/cdata.h"
#include "../include/support.h"
#include <stdlib.h>
#include <stddef.h>

#define SUCESSO 1
#define FRACASSO 0
PFILA2 threadsBlocked = NULL; //nao sei se é necessário fazer essa declaração
CreateFila2(PFILA2 threadsBlocked);

TCB_t * currentThreadOnExecution;

// Funcao que adiciona thread na fila de bloqueados
// Retorna 0 caso haja erro, 1 se der tudo certo.
int AddThreadToBlockingQueue(TCB_t * thread)
{
  int ret; // Referente a analise da funcao de AppendFila2, se der 0, a funcao funcionou, caso contrario nao
  thread->state = PROCST_BLOQ; // declara que a thread agora esta na fila de bloqueados
  ret = AppendFila2(threadsBlocked,thread);
  if(ret == 0)
    return SUCESSO;
  else
    return FRACASSO;
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
