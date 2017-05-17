#include "../include/cdata.h"
#include "../include/ready_queue.h"
#include <ucontext.h>
#include <stdlib.h>


/* escalonador de longo prazo vai usar as seguintes filas:

  - ready queue

*/



void createnewthread(TCB_t * novaThread)
{
  addThreadToReadyQueue(novaThread); // adiciona thread na fila de aptos
}

