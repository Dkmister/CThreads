#include "cdata.h"

TCB_t * getNextThreadToExecute();
TCB_t * removeThreadFromReadyQueue();
int * addThreadToReadyQueue(TCB_t * thread);
