#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "point_list.h"

int WriteInt(FILE *F, int n)
{  
  if (F == NULL)
    return -1;

  if (fputc(n, F) == EOF)
    return -1;
  n >>= 8;
  if (fputc(n, F) == EOF)
    return -1;
  n >>= 8;
  if (fputc(n, F) == EOF)
    return -1;
  
  return 1;
}

int ReadInt(FILE *F, int *n)
{
  if (F == NULL || n == NULL)
    return -1;

  int a, b, c;

  a = fgetc(F);
  if (a == EOF)
    return -1;
  b = fgetc(F);
  if (b == EOF)
    return -1;
  c = fgetc(F);
  if (c == EOF)
    return -1;
  
  *n = (c << 16) | (b << 8) | a;

  return 1;
}

void PointsPrint(intrusive_node *node, void *data)
{
  if (node == NULL || data == NULL)
    return;

  point_node *pt = get_point(node);
  printf((char *)data, pt->x, pt->y);
}

void PointsCount(intrusive_node *node, void *data)
{
  if (node == NULL || data == NULL)
    return;

  ++*((size_t *)data);
}

void PointsWriteT(intrusive_node *node, void *data)
{
  if (node == NULL || data == NULL)
    return;
  
  FILE *OF = data;

  point_node *pt = get_point(node);
  fprintf(OF, "%d %d\n", pt->x, pt->y);
}

void PointsWriteB(intrusive_node *node, void *data)
{
  if (node == NULL || data == NULL)
    return;
  
  FILE *OF = data;

  point_node *pt = get_point(node);
  if (WriteInt(OF, pt->x) != -1)
    WriteInt(OF, pt->y);    
}

int main(int argc, char *argv[]) 
{
  if (argc < 3)
    return 0;

  intrusive_list list;
  intrusive_list* l = &list;
  init_list(l);

  FILE *InF;
  int x, y;

  if (strcmp(argv[1], "loadtext") == 0)
  {
    if ((InF = fopen(argv[2], "r")) == NULL)
    {
      remove_all_points(l);
      return 0;
    }

    while (fscanf(InF, "%d %d", &x, &y) != -1)
        add_point(l, x, y);
  }
  else if (strcmp(argv[1], "loadbin") == 0)
  {
    if ((InF = fopen(argv[2], "rb")) == NULL)
    {
      remove_all_points(l);
      return 0;
    }

    while (ReadInt(InF, &x) != -1 && ReadInt(InF, &y) != -1)
        add_point(l, x, y);
  }
  else
  {
    remove_all_points(l);
    return 0;
  }
  
  fclose(InF);

  if (strcmp(argv[3], "savetext") == 0)
  {
    FILE *OF;

    if ((OF = fopen(argv[4], "w")) == NULL)
    {
      remove_all_points(l);
      return 0;
    }    

    apply(l, PointsWriteT, OF);

    fclose(OF); 
  }
  else if (strcmp(argv[3], "savebin") == 0)
  {
    FILE *OF;

    if ((OF = fopen(argv[4], "wb")) == NULL)
    {
      remove_all_points(l);
      return 0;
    }    

    apply(l, PointsWriteB, OF);

    fclose(OF); 
  }
  else if (strcmp(argv[3], "print") == 0)
  {
    apply(l, PointsPrint, argv[4]); 
    printf("\n");
  }
  else if (strcmp(argv[3], "count") == 0)
  {
    size_t cnt = 0;
    apply(l, PointsCount, &cnt); 
    printf("%zu\n", cnt);
  }
  remove_all_points(l);

  return 0;
}
