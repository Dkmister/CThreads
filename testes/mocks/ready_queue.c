#include "../../include/cdata.h"
#include "./include/thread.h"

TCB_t * removeThreadFromReadyQueue(int tid){
  return createMockThread();
}

int addThreadToReadyQueue(TCB_t * thread){
  return 0;
}

TCB_t * getNextThreadToExecute(){
  return createMockThread();
}
