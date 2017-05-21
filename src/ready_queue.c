#include "../include/cdata.h"
#include "../include/cthread.h"
#include "../include/support.h"
#include "../include/ready_queue.h"
#include <stdlib.h>



//  sao criadas as filas aqui mesmo
//  ou aqui só tem funções e as filas ficam sei la onde?
  PFILA2 pFilap0 = NULL;
	PFILA2 pFilap1 = NULL;
	PFILA2 pFilap2 = NULL;
	PFILA2 pFilap3 = NULL;


	CreateFila2(pFilap0);
	CreateFila2(pFilap1);
	CreateFila2(pFilap2);
  CreateFila2(pFilap3);
    






//-----  REVISAR -----
int addThreadToReadyQueue(TCB_t * thread)
{
  
  // muda o estado da thread para apto
  thread->state = 1;
  
	
	
	/* retorna -1 se der erro
		 retorn 0 se conseguir
	*/



  switch(thread->ticket)
  {
      // caso prioridade é 0
    case 0:
      if(AppendFila2(pFilap0, thread) == 0);
      //n botei ainda caso de falha no if
      break;
      
      // caso prioridade é 1
    case 1:
      if(AppendFila2(pFilap1, thread) == 0);
      break;
      
      // caso prioridade é 2
    case 2:
      if(AppendFila2(pFilap2, thread) == 0);
      break;
      
      // caso prioridade é 3
    case 3:
      if(AppendFila2(pFilap3, thread) == 0);
      break;
      
      // caso tenha um valor diferente para a prioridade 
    default:
      return -1;
  }
  
  return 0;
}









/* 
		TCB_t * getNextThreadToExecute():
		
    se conseguir retorna uma a thread de acordo com a prioridade dela
		se não conseguir retorna null;
*/


  TCB_t * getNextThreadToExecute()
  {
		
		TCB_t * threadToLeave;
		
		//CADA TESTE DE IF VERIFICA SE A FILA ESTÁ VAZIA
		//SE FOR DIFERENTE DE 0 SIGNIFICA QUE A LISTA ESTA VAZIA OU DEU ERRO
		//
		//
		//FIRSTFILA2: POE ITERADOR NO PRIMEIRO ELEMENTO DA FILA
		//GETATITERATORFILA2: PEGA O CONTEUDO DO ITERADOR
		//DELETEATITERATOR: DELETA O ELEMENTO DA FILA
		
		
		if(FirstFila2(pFilap0) == 0)
		{
			threadToLeave = GetAtIteratorFila2(pFilap0);
			
			DeleteAtIteratorFila2(pFilap0);
				
			return threadToLeave;			
				
	
		}else if(FirstFila2(pFilap1) == 0)
		  {
			 threadToLeave = GetAtIteratorFila2(pFilap1);
				
			 DeleteAtIteratorFila2(pFilap0);
				
			 return threadToLeave;		
	
		  }else if(FirstFila2(pFilap2) == 0)
			  {
			   	threadToLeave = GetAtIteratorFila2(pFilap2);
					
					DeleteAtIteratorFila2(pFilap0);
				
			    return threadToLeave;		
	
		  	}else if(FirstFila2(pFilap3) == 0)
				  {
						threadToLeave = GetAtIteratorFila2(pFilap3);
						
						DeleteAtIteratorFila2(pFilap0);
				
			       return threadToLeave;
						
			  	}else
					{
						return NULL;
					}
	}


    /*
		DO:iterador no primeiro da fila
			FirstFila2(PFILA2 pFila);
			TCB_t * threadToLeave;
			
			pega o conteudo do primeiro elemento e poe na thread pra ser executada
			threadToLeave = *GetAtIteratorFila2(PFILA2 pFila);
			
			
			deleta elemento
			DeleteAtIteratorFila2(PFILA2 pFila);
			
			
			
			ou:
			return threadToLeave;
  	*/

/*
	REMOVE THREAD DA READY QUEUE:
	
	TCB_t * ThreadParaRemover
	
	Para cada fila fazer:
	
	// seta iterador no primeiro elemento da fila
	FIRSTFILA2(pFila);
	
	// varre a fila até encontrar o elemento
	do
	{
		// ThreadParaRemover recebe o valor do iterador
		ThreadParaRemover = GetAtIteratorFila2(pFila)
		
		// se tid parametro é igual ao tid da thread atual no iterador:
		if(*ThreadParaRemover->tid == tid)
		{
			// deleta o elemento na fila
			DeleteAtIteratorFila2(pFila);
			
			// retorna a thread deletada
			return ThreadParaRemover;
		}
		
	}while(NextFila2(pFila) == 0);

*/



TCB_t * removeThreadFromReadyQueue(int tid)
{
	
		TCB_t *ThreadToRemove;
	
	
	
	// ----- FILA DE PRIORIDADE 0 -----
		FirstFila2(pFilap0);
	
	do
	{
		ThreadToRemove = GetAtIteratorFila2(pFilap0);
		
		if(ThreadToRemove->tid == tid)
		{
			DeleteAtIteratorFila2(pFilap0);
			
			return ThreadToRemove;
			
		}
		
	}while(NextFila2(pFilap0) == 0);
	
	
		
	
	// ----- FILA DE PRIORIDADE 1 -----
		FirstFila2(pFilap1);
	
	do
	{
		ThreadToRemove = GetAtIteratorFila2(pFilap1);
		
		if(ThreadToRemove->tid == tid)
		{
			DeleteAtIteratorFila2(pFilap1);
			
			return ThreadToRemove;
			
		}
		
	}while(NextFila2(pFilap1) == 0);
		
		
		

	// ----- FILA DE PRIORIDADE 2 -----
		FirstFila2(pFilap2);
	
	do
	{
		ThreadToRemove = GetAtIteratorFila2(pFilap2);
		
		if(ThreadToRemove->tid == tid)
		{
			DeleteAtIteratorFila2(pFilap2);
			
			return ThreadToRemove;
			
		}
		
	}while(NextFila2(pFilap2) == 0);
		
		
		
		
	// ----- FILA DE PRIORIDADE 3 -----
		FirstFila2(pFilap3);
	
	do
	{
		ThreadToRemove = GetAtIteratorFila2(pFilap3);
		
		if(ThreadToRemove->tid == tid)
		{
			DeleteAtIteratorFila2(pFilap3);
			
			return ThreadToRemove;
			
		}
		
	}while(NextFila2(pFilap3) == 0);
}  
