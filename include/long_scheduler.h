#include "../include/cdata.h"
#include "../include/ready_queue.h"
#include "../include/semaphore.h"
#include <ucontext.h>
#include <stdlib.h>


void createNewThread((void*) context, int prio);

int newTid();