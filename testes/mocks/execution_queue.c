#include "../../include/cdata.h"
#include "./include/thread.h"
#include <stdlib.h>

TCB_t * removeThreadFromExecutionQueue(){
 return createMockThread();
}

int addThreadToExecutionQueue(TCB_t * thread){
  return 0;
}
