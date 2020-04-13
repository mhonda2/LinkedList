#include <stdlib.h>
#include <string.h>
#include "dlist.h"

//---------------------------------------------------------------------------
dnode* dnode_create(int data, dnode* next, dnode* prev) {
  dnode* p = (dnode*)malloc(sizeof(dnode));
  p->data = data;
  p->next = next;
  p->prev = prev;
  return p;
}

//--------------------------------------------------------------------------
dlist* dlist_create() {
  dlist* p = (dlist*)malloc(sizeof(dlist));
  p->head = NULL;
  p->tail = NULL;
  p->size = 0;
  return p;
}

//-------------------------------------------------------------------------
bool dlist_empty(dlist* list) { return list->size == 0; }

//-------------------------------------------------------------------------
size_t dlist_size(dlist* list) { return list->size; }

//-------------------------------------------------------------------------
int dlist_front(dlist* list) {
  if(dlist_empty(list)) { fprintf(stderr, "List is empty\n"); exit(1); }
  return list->head->data;
}

//-------------------------------------------------------------------------
int dlist_back(dlist* list) {
  if(dlist_empty(list)) { fprintf(stderr, "List is empty\n"); exit(1); }
  return list->tail->data;
}

//-------------------------------------------------------------------------
void dlist_popfront(dlist* list) {
  if(dlist_empty(list)) { printf("List is empty\n"); return; }
  dnode* p = list->head;
  list->head = list->head->next;
  if(list->size != 1) { list->head->prev = NULL; }

  free(p);
  --list->size;
}

//------------------------------------------------------------------------
void dlist_popback(dlist* list) {
  if(dlist_empty(list)) { printf("List is empty\n"); return; }
  if(dlist_size(list) == 1) { dlist_popfront(list); return; }

  dnode* p = list->head;
  while (p->next != list->tail) { p = p->next; }
  p->next = NULL;
  list->tail->prev = NULL;
  free(list->tail);
  list->tail = p;
  --list->size;
}

//-----------------------------------------------------------------------
void dlist_pushfront(dlist* list, int data) {
  dnode* p = dnode_create(data, list->head, NULL);
  if(list->head != NULL) { list->head->prev = p; }
  list->head = p;
  if(list->size == 0) { list->tail = p; }
  ++list->size;
}

//-----------------------------------------------------------------------
void dlist_pushback(dlist* list, int data) {
  if(list->size == 0) { dlist_pushfront(list, data); return; }

  dnode* p = dnode_create(data, NULL, list->tail);
  list->tail->next = p;
  list->tail = p;
  ++list->size;
}

//-----------------------------------------------------------------------
void dlist_clear(dlist* list) {
  while (!dlist_empty(list)) {
    dlist_popfront(list);
  }
}

//-----------------------------------------------------------------------
void dlist_print(dlist* list, const char* msg) {
  printf("%s\n", msg);
  if(dlist_empty(list)) { printf("List is empty\n"); return; }

  dnode* p = list->head;
  while (p != NULL) {
    printf("%11p <-- %2d --> %p\n",p->prev, p->data, p->next);
    p = p->next;
  }
}
