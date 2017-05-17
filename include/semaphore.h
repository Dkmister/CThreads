
int newSemaphore(c_sem * semaphore);
int waitOnThread(int tid);
int waitOnSemaphore(c_sem * semaphore);
int releaseSemaphore(c_sem semaphore);
int releaseThread(int tid);
