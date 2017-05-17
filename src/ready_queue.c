#include "cdata.h"
#include <stdlib.h>



//  sao criadas as filas aqui mesmo
//  ou aqui só tem funções e as filas ficam sei la onde?

	CreateFila2(PFILA2 pFilap0);
	CreateFila2(PFILA2 pFilap1);
	CreateFila2(PFILA2 pFilap2);
  CreateFila2(PFILA2 pFilap3);
    


/*

TCB_t * removeThreadFromReadyQueue(int tid);
*/


//-----  REVISAR -----
int * addThreadToReadyQueue(TCB_t * thread)
{
  
  // muda o estado da thread para apto
  *thread->state = 1;
  
	
	
	/* retorna -1 se der erro
		 retorn 0 se conseguir
	*/
  switch(*thread->ticket)
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
      if(AppendFila2(pFilap3, thread) == o);
      break;
      
      // caso tenha um valor diferente para a prioridade 
    default:
      return -1;
  }
  
  return 0;
  }
  
/*

switch(*thread->ticket)
  {
      // caso prioridade é 0
    case 0:
      
      break;
      
      // caso prioridade é 1
    case 1:
      
      break;
      
      // caso prioridade é 2
    case 2:
      
      break;
      
      // caso prioridade é 3
    case 3:
      
      break;
      
      // caso tenha um valor diferente para a prioridade 
    default:
      return -1;
  }
  
  return 0;
  }


*/

/* 
		TCB_t * getNextThreadToExecute():
		
    se conseguir retorna uma a thread de acordo com a prioridade dela
		se não conseguir retorna null;
*/
  TCB_t * getNextThreadToExecute()
  {
		
		TCB_t * threadToLeave;
		
		//CADA DTESTE DE IF VERIFICA SE A FILA ESTÁ VAZIA
		//SE FOR DIFERENTE DE 0 SIGNIFICA QUE A LISTA ESTA VAZIA OU DEU ERRO
		//
		//
		//FIRSTFILA2: POE ITERADOR NO PRIMEIRO ELEMENTO DA FILA
		//GETATITERATORFILA2: PEGA O CONTEUDO DO ITERADOR
		//DELETEATITERATOR: DELETA O ELEMENTO DA FILA
		
		
		if(FirstFila2(pFilap0) == 0)
		{
			threadToLeave = *GetAtIteratorFila2(pFilap0);
			
			DeleteAtIteratorFila2(pFilap0);
				
			return threadToLeave;			
				
	
		}else if(FirstFila2(pFilap1) == 0)
		  {
			 threadToLeave = *GetAtIteratorFila2(pFilap1);
				
			 DeleteAtIteratorFila2(pFilap0);
				
			 return threadToLeave;		
	
		  }else if(FirstFila2(pFilap2) == 0)
			  {
			   	threadToLeave = *GetAtIteratorFila2(pFilap2);
					
					DeleteAtIteratorFila2(pFilap0);
				
			    return threadToLeave;		
	
		  	}else if(FirstFila2(pFilap3) == 0)
				  {
						threadToLeave = *GetAtIteratorFila2(pFilap3);
						
						DeleteAtIteratorFila2(pFilap0);
				
			       return threadToLeave;
						
			  	}else
					{
						return null;
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
  }
  

TCB_t * removeThreadFromReadyQueue(int tid)
{
	
	
	
	
	
	
	
	
}
  
  
  
}