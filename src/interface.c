#include "../include/cdata.h"
#include "../include/cthread.h"

#include "../include/errors.h"
#include "../include/semaphore.h"

#include "../include/ready_queue.h"
#include "../include/execution_queue.h"

#include "../include/short_scheduler.h"
#include "../include/medium_scheduler.h"

int ccreate (void* (*start)(void*), void *arg, int prio){

}

int csetprio(int tid, int prio){

}

int cyield(void){

}

int cjoin(int tid){
  return waitOnThread(tid);
}

int csem_init(csem_t *sem, int count){
  return newSemaphore(sem, count);
}

int cwait(csem_t *sem){
  return waitOnSemaphore(sem);
}

int csignal(csem_t *sem){
  return releaseSemaphore(sem);
}

int cidentify (char *name, int size){
  strcpy(name, "231060 G. Tassinari\n242276 V. Neto\n205680 J. Nakamura\n\0");
  return SUCCESS;
}
