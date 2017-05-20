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

// Retorna um inteiro, dizendo se a thread foi retirada da fila de bloqueados
/*
Percorre a fila de threads bloqueadas, e caso seja a thread com a tid selecionada
=> 1 = Retirada com SUCESSO
   0 = Sem Retirada, pois não está na fila
*/
int RemoveThreadFromBlockingQueue(int tid)
{
  TCB_t * thread = currentThreadOnExecution;

  while(FirstFila2(threadsBlocked)!= 0)
  {
    if((threadsBlocked->thread->tid)==tid){
      DeleteAtIteratorFila2(threadsBlocked);
      return SUCESSO
    }
    NextFila2(threadsBlocked);
  }
  return FRACASSO;

  //currentThreadOnExecution = findreferencedThread(tid);
  //currentThreadOnExecution = NULL; //Remove a thread atual
  //return thread; //Retorna a referencia da thread retirada
  /*
  if(thread->tid == tid){
    currentThreadOnExecution = NULL; //Remove a thread atual
    return thread; //Retorna a referencia da thread retirada
  }*/
}
