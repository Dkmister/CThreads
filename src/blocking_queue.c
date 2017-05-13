#include "../include/cdata.h"
#include <stdlib.h>
#include <stddef.h>

TCB_t * currentThreadOnExecution;

AddThreadToBlockingQueue(TCB_t * thread)
{
  if(currentThreadOnExecution != NULL)
  {
    return -1;
  }
  currentThreadOnExecution = thread;
  return 0;
}
