#include "../include/cdata.h"
#include "../include/execution_queue.h"
#include "../include/ready_queue.h"
#include <ucontext.h>
#include <stdlib.h>


void executeNextThread(){
  TCB_t * oldExecutingThread = removeThreadFromExecutionQueue(); //Remove a thread atual da fila de execução
  TCB_t * nextThread = getNextThreadToExecute(); //Pede a próxima thread a ser executada para a fila de aptos
  removeThreadFromReadyQueue(nextThread->tid); //Remove a próxima thread da fila de aptos
  addThreadToExecutionQueue(nextThread); //Adiciona a nova thread na fila de execução


  if(oldExecutingThread != NULL){ //Se havia uma thread em execução
    addThreadToReadyQueue(oldExecutingThread); //Adiciona a antiga thread na fila de aptos
    getcontext(&oldExecutingThread->context); //Salva o contexto atual na antiga thread
  }

  int * isReturningFromExecution = malloc(sizeof(int)); //Flag para saber se estamos retornando do contexto salv na antiga thread
  *isReturningFromExecution = 0;
  if(!*isReturningFromExecution){ //Se não estiver voltando o contexto
    *isReturningFromExecution = 1; //Seta a flag para que, na próxima vez, saibamos que estamos voltando do contexto
    setcontext(&nextThread->context); //Executa o contexto da próxima thread
  }
}
