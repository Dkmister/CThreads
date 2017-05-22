#include "../include/cdata.h"
#include "../include/support.h"
#include "../include/errors.h"
#include <stdlib.h>
#include <stddef.h>

PFILA2 threadsBlocked = NULL; //nao sei se é necessário fazer essa declaração

// Funcao que adiciona thread na fila de bloqueados
// Retorna 0 caso haja erro, 1 se der tudo certo.
int AddThreadToBlockingQueue(TCB_t * thread)
{
  initializeQueue();
  thread->state = 3; // declara que a thread agora esta na fila de bloqueados
  if(AppendFila2(threadsBlocked,thread) != ERROR){
    return SUCCESS;
  }
  return ERROR;
}

// Retorna um inteiro, dizendo se a thread foi retirada da fila de bloqueados
/*
Percorre a fila de threads bloqueadas, e caso seja a thread com a tid selecionada
=> 1 = Retirada com SUCESSO
   0 = Sem Retirada, pois não está na fila
*/
TCB_t * RemoveThreadFromBlockingQueue(int tid)
{
  initializeQueue();
  if(FirstFila2(threadsBlocked) != ERROR){
    do{
      TCB_t * thread = GetAtIteratorFila2(threadsBlocked);
      if(thread->tid == tid){
        DeleteAtIteratorFila2(threadsBlocked);
        return thread;
      }
    }while(NextFila2(threadsBlocked) != ERROR);
  }
  return NULL;
}

void initializeQueue(){
  if(threadsBlocked == NULL){
    threadsBlocked = malloc(sizeof(FILA2));
    CreateFila2(threadsBlocked);
  }
}
