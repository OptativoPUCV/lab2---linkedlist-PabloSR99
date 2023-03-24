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

List * createList() {
     List *list = (List*) malloc(sizeof(List));
     if (list == NULL) return NULL; 
     list->head=NULL;
     list->tail=NULL;
     list->current=NULL; 
     return list;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL)
      return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL)
      return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node * nodoNuevo = createNode(data);
    nodoNuevo->next = list->head;
    if (list->head == NULL && list->tail == NULL)
    {
      list->head = nodoNuevo;
      list->tail = nodoNuevo;
    }
    list->head->prev = nodoNuevo;
    list->head = nodoNuevo;
      
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {  
  Node *nodoNuevo = createNode(data);

  if (list->current == list->tail)
  {
    list->tail->next = nodoNuevo;
    nodoNuevo->prev = list->tail;
    list->tail = nodoNuevo;
    list->current = nodoNuevo;
  }

  if (list->current->next != NULL)
  {
    Node *aux = list->current->next;
    nodoNuevo->next = aux;
    nodoNuevo->prev = list->current;
    list->current->next = nodoNuevo;
    aux->prev = nodoNuevo;
    list->current = nodoNuevo;
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

void * popCurrent(List * list) {

    void *dato = list->current->data; 
    if (list->current == list->head)
    {
      Node *aux = list->current->next;
      aux->prev = NULL;
      list->head = aux;
      free(list->current);
      list->current = aux;
      return dato;
    }
    if (list->current == list->tail)
    {
       Node *aux = list->current->prev;
       aux->next = NULL;
       list->tail = aux;
       free(list->current);
       list->current = aux;
      return dato;
    }
    Node *aux_next = list->current->next;
    Node *aux_prev = list->current->prev;
    aux_next->prev = aux_prev;
    aux_prev->next = aux_next;
    free(list->current);
    list->current = aux_next;
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}