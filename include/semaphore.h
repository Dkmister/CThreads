
int newSemaphore(csem_t * semaphore, int maxThreadsOnResource);
int waitOnThread(int tid);
int waitOnSemaphore(csem_t * semaphore);
int releaseSemaphore(csem_t semaphore);
int releaseThread(int tid);