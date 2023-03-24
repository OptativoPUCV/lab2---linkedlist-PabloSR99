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

  if (list->current->next == NULL)
  {
    list->current->next = nodoNuevo;
    nodoNuevo->prev = list->current;
    nodoNuevo->next = list->tail;
    list->tail->prev = nodoNuevo;
  }

  
  if (list->current->next != NULL)
  {
    nodoNuevo->prev = list->current;
    list->current->next->prev = nodoNuevo;
    nodoNuevo->next = list->current->next;
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

    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    
    return list->current->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}