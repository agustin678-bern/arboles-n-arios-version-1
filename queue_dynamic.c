#include <stdio.h>
#include <stdlib.h>
#include "queue_dynamic.h"

typedef struct queue_node {
  QUEUE_ELEM value;
  struct queue_node *next;
} queue_node;

typedef struct _queue {
  queue_node *head;
  queue_node *tail;
  int maxsize; // -1 for no limit
  int count;
}queue;

queue_node* new_node_q(QUEUE_ELEM val){
  queue_node* res=malloc(sizeof(queue_node));
  if(res!=NULL){
    res->value=val;
    res->next=NULL;
  }
  return res;
}
queue* queue_new () {
  queue* q = malloc(sizeof(queue));

  q->head = NULL;
  q->tail = NULL;
  q->maxsize = -1; // no limit
  q->count = 0;

  return q;
}

queue* queue_new_with (int maxsize) {
  queue* q = malloc(sizeof(queue));

  q->head = NULL;
  q->tail = NULL;
  q->maxsize = maxsize;
  q->count = 0;

  return q;
}

void queue_free (queue* q) {
  if(q==NULL)return;
  free(q);
}

int queue_getsize (queue* q) {
  if(q==NULL)return -1;
  return q->count;
}

int queue_getmaxsize (queue* q) {
  if(q==NULL)return -2;
  return q->maxsize;
}

int queue_isfull (queue* q) {
  if(q==NULL)return 0;
  if(q->maxsize==-1)return 0;
  if(q->count>=q->maxsize){
    return 1;
  }else return 0;
}

int queue_isempty (queue* q) {
 if(q==NULL)return 0;
 
 return (q->count==0)? 1 : 0;
}

void enqueue (queue* q, QUEUE_ELEM elem) {
  if(q!=NULL && !queue_isfull(q)){
    queue_node* nuevo=new_node_q(elem);
    if(nuevo!=NULL){
      if(queue_isempty(q)){
        q->head=nuevo;
        q->tail=nuevo;
      }
      else{
        q->tail->next=nuevo;
        q->tail=nuevo;
      }
      q->count++;
    }
  }
}

QUEUE_ELEM dequeue (queue* q) {

  if(q==NULL || queue_isempty(q)) return QUEUE_ELEM_DEFAULT;

  queue_node* aux=q->head;
  q->head=aux->next;
  aux->next=NULL;

  QUEUE_ELEM val=aux->value;
  free(aux);
      
  q->count--;
    
  if(queue_isempty(q)){
    q->tail=NULL;
  }
  return val;
}

QUEUE_ELEM peek (queue* q) {
  QUEUE_ELEM result=QUEUE_ELEM_DEFAULT;
  if(q!=NULL && !queue_isempty(q)){
    result=q->head->value;
  }
  return result;
}