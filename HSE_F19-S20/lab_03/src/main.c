#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <flite.h>
#include <string.h>
#include <memory.h>

#include "clist.h"

cst_voice *register_cmu_us_kal(const char *voxdir);

struct point 
{
  int x, y;
  struct intrusive_node node;
};

typedef struct point point_t;

void add_point(intrusive_list_t *l, int x, int y) 
{
  point_t *pt;

  if (l == NULL)
    return;
  
  pt = (point_t *)malloc(sizeof(point_t));
  
  //printf("%p\n", pt->node);
  //printf("%p\n", tmp);

  pt->node.next = pt->node.prev = NULL;
  add_node(l, &(pt->node));

  pt->x = x;
  pt->y = y;
}

void remove_point(intrusive_list_t *l, int x, int y) 
{
  intrusive_node_t *cur, *tmp;
  
  if (l == NULL)
    return;
  
  cur = l->head;
  while (cur != NULL)
  {
    tmp = cur->next;
    point_t *pt = container_of(cur, struct point, node);

    if (pt->x == x && pt->y == y)
    {
      remove_node(l, cur);
      //printf("Deleted node");
      free(pt);
    }
    cur = tmp;
  }
}

void show_all_points(intrusive_list_t *l, char *Buf) 
{
  intrusive_node_t *cur;
  int j = 0;

  if (l == NULL)
    return;
  
  cur = l->head;
  while (cur != NULL)
  {
    point_t *pt = container_of(cur, struct point, node);
    
    //printf("%p\n", pt);
    //printf("%p\n", cur);
    j += sprintf(Buf + j, "(%d %d) ", pt->x, pt->y);
    printf("(%d %d) ", pt->x, pt->y);
    cur = cur->next;
  }
  printf("\n");
}

void remove_all_points(intrusive_list_t *l) 
{
  intrusive_node_t *cur, *tmp;
  
  if (l == NULL)
    return;
  
  cur = l->head;
  while (cur != NULL)
  {
    point_t *pt = container_of(cur, struct point, node);
    
    //printf("%p, %p\n", cur, cur->next);
    tmp = cur->next;
    remove_node(l, cur);
    free(pt);
    cur = tmp;
  }
}


int main(void) 
{
  intrusive_list_t l;
  char buf[100];
  char Out[10000];
  //printf("%ld\n", offsetof(struct point, y));

  cst_voice *v;

  flite_init();

  v = register_cmu_us_kal(NULL);

  init_list(&l);

  while (1)
  {
    scanf("%99s", buf);

    if (!strcmp(buf, "add"))
    {
      int x, y;

      scanf("%d%d", &x, &y);
      add_point(&l, x, y);
    }
    else if (!strcmp(buf, "rm"))
    {
      int x, y;

      scanf("%d%d", &x, &y);
      remove_point(&l, x, y);
    }
    else if (!strcmp(buf, "print"))
    {
      show_all_points(&l, Out);
      //printf("%s", Out);

    flite_text_to_speech(Out, v, "play");
    }
    else if (!strcmp(buf, "rma"))
      remove_all_points(&l);
    else if (!strcmp(buf, "len"))    
      printf("%d\n", get_length(&l));
    else if (!strcmp(buf, "exit"))
      break;
    else
      printf("Unknown command\n");
  }
  remove_all_points(&l);
  
  return 0;
}