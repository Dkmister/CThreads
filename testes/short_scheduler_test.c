#include "../include/short_scheduler.h"
#include "../include/execution_queue.h"
#include <stdio.h>


/*
  Este teste tem por objetivo garantir que o escalonador de curto prazo executa corretamente uma thread retornada
  pela fla de aptos.

  Espera-se que, quando chamada, a função executeNextThread execute a thread retornada pelo versão mock da fila de aptos.
  Dessa maneira, espera-se como saída:

        Iniciando teste de execução de thread

        Esta função é executada pelo thread mock da fila de aptos!

  Lembrando que, como a fila de aptos está sendo mockada, não há nenhuma função a ser executada ao fim da thread.
  Portanto, um segmentation fault é esperado!
*/

int main(){
  printf("Iniciando teste de execução de thread\n");
  executeNextThread();
  return 0;
}
