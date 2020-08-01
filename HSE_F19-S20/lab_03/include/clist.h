#ifndef CLIST_H_
#define CLIST_H_

#include <stddef.h>

struct intrusive_node 
{
  struct intrusive_node *next;
  struct intrusive_node *prev;
};

struct intrusive_list 
{
  struct intrusive_node *head;
};

typedef struct intrusive_node intrusive_node_t;
typedef struct intrusive_list intrusive_list_t;

void init_list(intrusive_list_t *list);
void add_node(intrusive_list_t *list, intrusive_node_t *node);
void remove_node(intrusive_list_t *list, intrusive_node_t *node);

int get_length(intrusive_list_t *list);

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

#endif