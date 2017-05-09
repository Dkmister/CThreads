#include "../include/cdata.g"
#include "../include/execution_queue.h"
// #include "../ready_queue.h"

void executeNextThread(){
  TCB_t * oldExecutingThread;
  // TODO : remover thread atual da fila de execução e coloca-la na fila de aptos
  // if(oldExecutingThread = removeThreadFromExecutionQueue()){
  //   addThreadToReadyQueye(oldExecutingThread);
  // }
  TCB_t * nextThread = getNextThreadToExecute();
  //TODO : Retirar thread da fila de aptos, se necessário! (Depende da arquitetura).
  addThreadToExecutionQueue(nextThread);
}
