#include "cdata.h"

typedef struct dlqueue{
  TCB_t* current_thread;
  struct dlqueue* next;
  struct dlqueue* prev;
}2LQueue;

typedef struct dlqlist{
  2LQueue* head;
  2LQueue* tail;
}2LQList;


int enqueue(2LQList*, TCB_t *);
int dequeue(2LQList*);
2LQueue* front(2LQList*);
void nullify(2LQList*);
int empty?(2LQList*);
void print_queue(2LQList* );


int dequeue_anywhere(2LQList*s ,TCB_t *);
void remove_element(2LQList* s, 2LQueue* d);
