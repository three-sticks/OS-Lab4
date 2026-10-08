#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *list_alloc() {
  list_t *l = (list_t *)malloc(sizeof(list_t));
  if (l == NULL) return NULL;
  l->head = NULL;
  return l;
}

void list_free(list_t *l){
  if(l == NULL) return;
  node_t *cur = l->head;
  while (cur != NULL) {
    node_t *next = cur->next;
    free(cur);
    cur = next;
  }
  free(l);
}

int list_length(list_t *l){
  int count = 0;
  node_t *cur = l->head;
  while (cur != NULL) {
    count ++;
    cur = cur->next;
  }
  return count;
}

char *listToString(list_t *l){
  int len = list_length(l);
  size_t size = (size_t)len*13 + 5;
  char *buf = (char *)malloc(size);
  if (buf == NULL) return NULL;
  buf[0] = '\0';

  char tmp[16];
  node_t *cur = l->head;
  while (cur != NULL) {
    sprintf(tmp, "%d->", cur->value);
    strcat(buf, tmp);
    cur = cur->next;
  }
  strcat(buf, "NULL");
  return buf;
}

void list_add_to_back(list_t *l, elem value){
  node_t *n = (node_t *)malloc(sizeof(node_t));
  if (n == NULL) return;
  n->value = value;
  n->next = NULL;

  if (l->head == NULL){
    l->head = n;
    return;
  }
  node_t *cur = l->head;
  while(cur->next != NULL) cur = cur ->next;
  cur->next = n;
}

void list_add_to_front(list_t *l, elem value){
  node_t *n = (node_t *)malloc(sizeof(node_t));
  if(n == NULL) return;
  n->value = value;
  n->next = l->head;
  l->head = n;
}

void list_add_at_index(list_t *l, int index, elem value){
  if (index < 0 || index >list_length(l)) return;
  if (index == 0) {
    list_add_to_front(l, value);
    return;
  }
  node_t *prev = l->head;
  for (int i = 0; i <index - 1; i++) prev = prev-> next;

  node_t *n = (node_t *)malloc(sizeof(node_t));
  if (n == NULL) return;
  n->value = value;
  n->next = prev->next;
  prev->next = n;
}

elem list_remove_from_back(list_t *l){
  if (l->head == NULL) return -1;

  node_t *cur = l->head;
  if (cur->next == NULL) {
    elem v = cur->value;
    free(cur);
    l->head = NULL;
    return v;
  }
  while (cur->next->next != NULL) cur = cur->next;
  elem v = cur->next->value;
  free(cur->next);
  return v;
}

elem list_remove_from_front(list_t *l){
  if (l->head == NULL) return -1;
  node_t * old = l->head;
  elem v = old->value;
  l->head = old->next;
  free(old);
  return v;
}

elem list_remove_at_index(list_t *l, int index){
  if (index < 0|| index >= list_length(l)) return -1;
  if (index == 0) return list_remove_from_front(l);

  node_t *prev = l->head;
  for (int i = 0; i <index - 1; i++) prev = prev->next;
  node_t *target = prev->next;
  elem v = target->value;
  prev->next = target->next;
  free(target);
  return v;
}

elem list_get_elem_at(list_t *l, int index){
  if (index < 0 || index >= list_length(l)) return -1;
  node_t *cur = l->head;
  for (int i=0; i < index; i++) cur = cur->next;
  return cur->value;
}