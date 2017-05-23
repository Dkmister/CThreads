#include "cdata.h"

TCB_t * getNextThreadToExecute();
TCB_t * removeThreadFromReadyQueue(int tid);
int addThreadToReadyQueue(TCB_t * thread);
void initReadyQueue();
