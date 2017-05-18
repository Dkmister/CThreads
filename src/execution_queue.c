#include "../include/cdata.h"
#include <stdlib.h>


TCB_t * currentThreadOnExecution;

/*
  Função que retira a atual thread da fila de execução e retorna um ponteiro
  para a sua estrutura TCB.
*/
TCB_t * removeThreadFromExecutionQueue(){
  TCB_t * thread = currentThreadOnExecution; //Salva a referencia à atual thread
  currentThreadOnExecution = NULL; //Remove a thread atual
  return thread; //Retorna a referencia da thread retirada
}

/*
  Função que adiciona uma thread na fila de execução.
  Caso haja algum erro, retorna -1;
*/
int addThreadToExecutionQueue(TCB_t * thread){
  if(currentThreadOnExecution != NULL){ //Se ja existe uma thread
    return -1; //Retornar erro
  }
  currentThreadOnExecution = thread; //Seta a nova thread
  currentThreadOnExecution->state = 2; //EXECUÇÂO
  return 0; //Retornar sucesso
}

TCB_t * getCurrentThread(){
  return currentThreadOnExecution;
}
