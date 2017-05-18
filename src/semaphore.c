#include "../include/cthread.h"
#include "../include/support.h"
#include "../include/execution_queue.h"
#include "../include/short_scheduler.h"
#include "../include/errors.h"
// #include "../include/.medium_term_scheduler.h"

PFILA2 threadSemaphores = NULL;

typedef struct threadSemaphore {
  int threadTid;
  csem_t * semaphore;
} threadSemaphore;

int newSemaphore(csem_t * semaphore, int maxThreadsOnResource){
  PFILA2 fila;
  if(!CreateFila2(fila)){ //inicializa uma fila
    return ERROR;
  }
  csem_t newSemaphore = malloc(sizeof(csem_t));
  newSemaphore->count = maxThreadsOnResource; //inicializa o contador do semáforo
  newSemaphore->fila = fila;
  return SUCCESS;
}

int waitOnSemaphore(csem_t * semaphore){
  if(semaphore->count > 0){ //Se o semáforo ainda puder ser decrementado (recurso pode ser alocado)
    semaphore->count = semaphore->count - 1; //Decrementa o contador do semáforo
  } else { //Se o semáforo ja estiver ocupado (recurso não pode mais ser alocado)
    TCB_t * currentThread = getCurrentThread(); //pega a thread atualmente em execução
    if(!AppendFila2(semaphore->fila, (void*)currentThread)){ //Coloca a thread na fila de espera do semáforo
      return ERROR;
    }
    BlockCurrentThread(); //Bloqueia a thread atual e executa a próxima
  }
  return SUCCESS;
}

int releaseSemaphore(csem_t semaphore){
  semaphore->count = semaphore->count + 1;
  if(LastFila2(semaphore->fila)){
    TCB_t * waitingThread = (TCB_t *)GetAtIteratorFila2(semaphore->fila); //Testar por erro
    semaphore->count = semaphore->count - 1;
    UnblockThread(waitingThread->tid);
    DeleteAtIteratorFila2(fila); //Testar por erro
  }
}

int waitOnThread(int tid){
  if(!threadSemaphores){ //Se a fila ainda não existir
    CreateFila2(threadSemaphores); //inicializa a fila
  }
  csem_t * semaphore;
  if(searchThreadSemaphore(tid, semaphore) == ERROR{ //Procura a estrutura de semáforo referente à thread referenciada por tid;
    return ERROR; //Se houver erro, retorna erro
  }
  semaphore->count = semaphore->count - 1; //Decrementa o contador do semáforo
  if(semaphore->count < 0){ //Se o semaoro já estava ocupado (contador era 0)
    semaphore->count = semaphore->count + 1; //Incrementa o semáforo para voltar ao contador anterior
    TCB_t * currentThread = getCurrentThread(); //Pega a thread atualmente em execuçãp
    AppendFila2(semaphore->fila, (void*) currentThread); //Coloca a thread na fila do semáforo
    BlockCurrentThread(); //Bloqueia a thread atual
  }
  return SUCCESS; //Retorna sucesso
}

int releaseThread(int tid){
  csem_t semaphore;
  if(searchThreadSemaphore(tid, semaphore) == ERROR){ //Procura a thread na fila de semáforos
    return ERROR;
  }
  if(FirstFila2(semaphore->fila)){
    while(FirstFila2(semaphore->fila)){ //Para cada thread esperando por ela
      TCB_t * thread = (TCB_t *)GetAtIteratorFila2(semaphore->fila);
      UnblockThread(thread) //Desbloquear (adicionar à fila de aptos)
    }
  } else {
    return ERROR;
  }
  return SUCCESS;
}

int searchThreadSemaphore(int tid, csem_t * semaphore){
  if(FirstFila2(threadSemaphores)){ //Se a fila não estiver vazia
    threadSemaphore * thSemaphore;
    do{ //Itera na fila até achar o semáforo
      thSemaphore = GetAtIteratorFila2();
      if(thSemaphore->threadTid == tid){ //Se achou a estrutura da thread
        semaphore = thSemaphore->semaphore; //Se achar, retorna o semaforo
        return SUCCESS;
      }
    }while(NextFila2(threadSemaphores));
  }
  return ERROR; //Se não achou nada, retorna null
}
