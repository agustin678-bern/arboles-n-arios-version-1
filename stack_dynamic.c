#include <stdio.h>
#include <stdlib.h>
#include "stack_dynamic.h"

typedef struct _stack_node {
  STACK_ELEM value;
  struct _stack_node *next;
} stack_node;

typedef struct _stack {
  stack_node *head;
  int maxsize; // -1 for no limit
  int count;
} stack;

stack_node* node_new(STACK_ELEM val){
  stack_node* res=malloc(sizeof(stack_node));
  if(res!=NULL){
  res->value=val;
  res->next=NULL;
  }
  return res;
}
stack* stack_new() {
  stack* nuevo=malloc(sizeof(stack));
  if(nuevo!=NULL){
    nuevo->count=0;
    nuevo->head=NULL;
    nuevo->maxsize=-1;
  }
  return nuevo;
}

stack* stack_new_with(int maxsize) {
  stack* nuevo=malloc(sizeof(stack));
  if(nuevo!=NULL){
    nuevo->count=0;
    nuevo->head=NULL;
    nuevo->maxsize=maxsize;
  }
  return nuevo;
}

void stack_free(stack* s) {
  if(s==NULL)return;
  free(s);
}


int stack_getsize(stack* s) {
  if(s==NULL)return -1;
  return s->count;
}

int stack_getmaxsize(stack* s) {
  if(s==NULL)return 0;
  return s->maxsize;
}

int stack_isempty(stack* s) {
  if(s==NULL)return 0;
  return(s->count==0);
}

int stack_isfull(stack* s) {
  if(s==NULL)return 0;
  return (s->count==s->maxsize);
}

void push(stack* s, STACK_ELEM elem) {
  if(s==NULL || stack_isfull(s))
  return;

  stack_node* n=node_new(elem);
  if(n==NULL)return;

  n->next=s->head;
  s->head=n;
  s->count++;
}

STACK_ELEM pop(stack* s) {
  if(s==NULL || stack_isempty(s))
  return STACK_ELEM_DEFAULT;
  stack_node* aux=s->head;
  s->head=aux->next;
  STACK_ELEM res=aux->value;
  free(aux);
  s->count--;
  return res;
}

STACK_ELEM top(stack* s) {
  if(s==NULL || stack_isempty(s))return STACK_ELEM_DEFAULT;
  return s->head->value;
}

void stack_destroy(stack* s, void elem_free(STACK_ELEM)){
  if(s==NULL)return;
  if(elem_free==NULL){
    while(!stack_isempty(s)){
      pop(s);
    }
  }else{
    while(!stack_isempty(s)){
      elem_free(pop(s));
    }
  }
  stack_free(s);
}