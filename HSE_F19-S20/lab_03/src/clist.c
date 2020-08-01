#include <stdlib.h>

#include "clist.h"

void init_list(intrusive_list_t *list)
{
  if (list == NULL)
    return;

  list->head = NULL;
}

void add_node(intrusive_list_t *list, intrusive_node_t *node)
{
  if (list == NULL || node == NULL)
    return;
  
  if (list->head != NULL)
  {
    node->next = list->head;
    list->head->prev = node;
  }
  list->head = node;
}

void remove_node(intrusive_list_t *list, intrusive_node_t *node)
{
  intrusive_node_t *cur;

  if (list == NULL || list->head == NULL || node == NULL)
    return;
  if (list->head == node)
  {
    list->head = list->head->next;
    if (list->head != NULL)
      list->head->prev = NULL;

    return;
  }
  cur = list->head;

  while (cur->next != NULL && cur->next != node)
    cur = cur->next;

  if (cur->next == NULL)
      return;
  
  if (node->next != NULL)
  	node->next->prev = cur;
  cur->next = node->next;
}

int get_length(intrusive_list_t *list)
{
  intrusive_node_t *cur;
  int cnt = 0;

  if (list->head == NULL)
    return 0;
  
  cur = list->head;

  while (cur != NULL)
    ++cnt, cur = cur->next;

  return cnt;
}