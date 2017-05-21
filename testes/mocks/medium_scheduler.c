#include "../../include/cdata.h"
#include "./include/thread.h"
#include <stdio.h>

TCB_t * BlockCurrentThread(){
  printf("Bloqueando uma thread\n");
  return createMockThread();
}

int UnblockThread(int tid){
  printf("Thread %d desbloqueada\n", tid);
  return 0;
}
