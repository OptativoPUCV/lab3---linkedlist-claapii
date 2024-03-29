#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
  List* list = (List*)malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  return list;
}

void *firstList(List * list) 
{
  if(list->head == NULL)
    return 0;
  
  list->current = list->head;
  return list->current->data;
}

void *nextList(List * list) 
{
  if(list->current == NULL)
    return 0;
  if(list->current->next == NULL)
    return 0;
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) 
{
  if(list->tail == NULL)
    return 0;
  list->current = list->tail;
  return list->current->data;
}

void * prevList(List *list) 
{
  if(list->current == NULL)
    return 0;
  if(list->current->prev == NULL)
    return 0;
  list->current = list->current->prev;
  return list->current->data;
} 

void pushFront(List * list, void * data) 
{
  Node* nuevoNodo = createNode(data);
  if(list->head == NULL)
  {
    list->head = nuevoNodo;
    list->tail = nuevoNodo;
  }
  else
  {
    nuevoNodo->next = list->head;
    list->head->prev = nuevoNodo;
    list->head = nuevoNodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
  Node* nuevoNodo = createNode(data);
  if(list->current == NULL)
  {
    pushFront(list,data); //Verifica que sea una lista vacía y lo pone en el primer elemento
  }
  else
  {
    nuevoNodo->prev = list->current;
    nuevoNodo->next = list->current->next;
    if(list->current->next == NULL) //En caso de ser el último elemento (current) ponemos que tail = nuevoNodo
    {
      list->tail = nuevoNodo;
    }
    list->current->next = nuevoNodo;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
  if(list->current == NULL)
    return 0;
  if(list->current == list->head) //Verificar que sea el primero
  {
    list->head = list->head->next;
    list->current = list->head;
  }
  if(list->current == list->tail) //Verificar que sea el último
    list->tail = list->tail->prev;
  list->current->prev->next = list->current->next;
  list->current->next->prev = list->current->prev;
  list->current = list->current->next;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}