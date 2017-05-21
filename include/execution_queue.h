#include "cdata.h"

TCB_t * getCurrentThread();
TCB_t * removeThreadFromExecutionQueue();
int addThreadToExecutionQueue(TCB_t * thread);
