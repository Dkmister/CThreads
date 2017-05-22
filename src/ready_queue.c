#include "../include/cdata.h"
#include "../include/cthread.h"
#include "../include/support.h"
#include "../include/errors.h"
#include <stdlib.h>


PFILA2 pFilap0 = NULL;
PFILA2 pFilap1 = NULL;
PFILA2 pFilap2 = NULL;
PFILA2 pFilap3 = NULL;


/* retorna -1 se der erro
retorn 0 se conseguir
*/
int addThreadToReadyQueue(TCB_t * thread)
{
  thread->state = 1; //Muda o estado da thread para apto
  PFILA2 correctQueue;
  switch(thread->ticket)
  {
    // caso prioridade é 0
    case 0:
      if(pFilap0 == NULL){
         pFilap0 = malloc(sizeof(FILA2));
         CreateFila2(pFilap0);
      }
      correctQueue = pFilap0;
      break;
    // caso prioridade é 1
    case 1:
      if(pFilap1 == NULL){
         pFilap1 = malloc(sizeof(FILA2));
         CreateFila2(pFilap1);
      }
      correctQueue = pFilap1;
      break;
    // caso prioridade é 2
    case 2:
      if(pFilap2 == NULL){
         pFilap2 = malloc(sizeof(FILA2));
         CreateFila2(pFilap2);
      }
      correctQueue = pFilap2;
      break;
    // caso prioridade é 3
    case 3:
      if(pFilap3 == NULL){
         pFilap3 = malloc(sizeof(FILA2));
         CreateFila2(pFilap3);
      }
      correctQueue = pFilap3;
      break;
    default:
      return ERROR;
      break;
  }


  if(AppendFila2(correctQueue, thread) == ERROR){
    return ERROR;
  }

  return SUCCESS;
}

/*
TCB_t * getNextThreadToExecute():

se conseguir retorna uma a thread de acordo com a prioridade dela
se não conseguir retorna null;
*/
TCB_t * getNextThreadToExecute()
{

  PFILA2 firstNotEmptyQueue;

  if(pFilap0 != NULL && FirstFila2(pFilap0) == 0){
    printf("\nfila 0\n");
    firstNotEmptyQueue = pFilap0;
  }else if(pFilap1 != NULL && FirstFila2(pFilap1) == 0){
    printf("\nfila 1\n");
    firstNotEmptyQueue = pFilap1;
  }else if(pFilap2 != NULL && FirstFila2(pFilap2) == 0){
    printf("\nfila 2\n");
    firstNotEmptyQueue = pFilap2;
  }else if(pFilap3 != NULL && FirstFila2(pFilap3) == 0){
    printf("\nfila 3\n");
    firstNotEmptyQueue = pFilap3;
  }else{
    printf("returnei null");
    return NULL;
  }

  TCB_t * threadToLeave;
  threadToLeave = GetAtIteratorFila2(firstNotEmptyQueue);
  printf("\npróxima : %d\n", threadToLeave->tid);
  DeleteAtIteratorFila2(firstNotEmptyQueue);
  return threadToLeave;
}


TCB_t * removeThreadFromReadyQueue(int tid)
{

  TCB_t * ThreadToRemove;

  if(pFilap0 != NULL && FirstFila2(pFilap0) == SUCCESS){
    do{
      ThreadToRemove = GetAtIteratorFila2(pFilap0);
      if(ThreadToRemove->tid == tid){
        DeleteAtIteratorFila2(pFilap0);
        return ThreadToRemove;
      }
    }while(NextFila2(pFilap0) == SUCCESS);
  } else if(pFilap1 != NULL && FirstFila2(pFilap1) == SUCCESS){
    do{
      ThreadToRemove = GetAtIteratorFila2(pFilap1);
      if(ThreadToRemove->tid == tid){
        DeleteAtIteratorFila2(pFilap1);
        return ThreadToRemove;
      }
    }while(NextFila2(pFilap1) == SUCCESS);
  } else if(pFilap2 != NULL && FirstFila2(pFilap2) == SUCCESS){
    do{
      ThreadToRemove = GetAtIteratorFila2(pFilap2);
      if(ThreadToRemove->tid == tid)
      {
        DeleteAtIteratorFila2(pFilap2);
        return ThreadToRemove;
      }
    }while(NextFila2(pFilap2) == SUCCESS);
  } else if(pFilap3 != NULL && FirstFila2(pFilap3) == SUCCESS){
    do{
      ThreadToRemove = GetAtIteratorFila2(pFilap3);
      if(ThreadToRemove->tid == tid){
        DeleteAtIteratorFila2(pFilap3);
        return ThreadToRemove;
      }
    }while(NextFila2(pFilap3) == 0);
  }

  return NULL;
}
