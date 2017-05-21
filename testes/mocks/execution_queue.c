#include "../../include/cdata.h"
#include "./include/thread.h"

TCB_t * removeThreadFromExecutionQueue(){
 return createMockThread();
}

int addThreadToExecutionQueue(TCB_t * thread){
  return 0;
}

TCB_t * getCurrentThread(){
 return createMockThread();
}
