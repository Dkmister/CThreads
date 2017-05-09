#include "../include/cdata.h"

TCB_t * currentThreadOnExecution;

/*
  Função que retira a atual thread da fila de execução e retorna um ponteiro
  para a sua estrutura TCB.
  Caso haja algum erro, retorna -1
*/
TCB_t * removeThreadFromExecutionQueue(){
  if(currentThreadOnExecution == NULL){ //Se não existe uma thread atualmente.
    return -1; // Retorna erro
  }
  TCB_t thread = currentThreadOnExecution; //Salva a referencia à atual thread
  currentThreadOnExecution = NULL; //Remove a thread atual
  return thread; //Retorna a referencia da thread retirada
}

/*
  Função que adiciona uma thread na fila de execução.
  Caso haja algum erro, retorna -1;
*/
void addThreadToExecutionQueue(TCB_t * thread){
  if(currentThreadOnExecution != NULL){ //Se ja existe uma thread
    return -1; //Retornar erro
  }
  currentThreadOnExecution = thread; //Seta a nova thread
  return 0; //Retornar sucesso
}
