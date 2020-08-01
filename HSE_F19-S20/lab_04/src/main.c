#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mergesort.h"

int int_lt_comparator(const void *a, const void *b)
{
  return *(int *)a - *(int *)b;
}

int char_lt_comparator(const void *a, const void *b)
{
  return *(char *)a - *(char *)b;
}

int string_lt_comparator(const void *a, const void *b)
{
  return strcmp(*((char **)a), *((char **)b));
}


int main(int argc, char *argv[])
{
  char *data_c = NULL;
  int *data_i = NULL;
  char *data = NULL;
  int i;
  size_t el_size, type = 0;
  int (*comparator)(const void *a, const void *b);
  
  if (argc < 3)
    return 0;
  //printf("%s", argv[1]);
  
  if (!strcmp(argv[1], "str"))
  {
    el_size = sizeof(char *);
    type = 0;

    data = (char *)(argv + 2);
    comparator = string_lt_comparator;
  }
  else if (!strcmp(argv[1], "int"))
  {
    el_size = sizeof(int);
    type = 1;

    data_i = malloc(el_size * (argc - 2));

    for (i = 0; i < argc - 2; ++i)
      data_i[i] = atoi(argv[i + 2]);

    data = (char *)data_i;
    comparator = int_lt_comparator;
  }
  else if (!strcmp(argv[1], "char"))
  {
    el_size = sizeof(char);
    type = 2;

    data_c = malloc(argc - 2);

    for (i = 0; i < argc - 2; ++i)
      data_c[i] = argv[i + 2][0];

    data = data_c;
    comparator = char_lt_comparator;
  }
  else
    return 0;

/*
  for (i = 0; i < argc - 2; ++i)
    printf("%s ", argv[i + 2]);
  printf("\n");
*/

  mergesort(data, argc - 2, el_size, comparator);

  if (type == 0)
    for (i = 0; i < argc - 2; ++i)
      printf("%s ", ((char **)data)[i]);
  else if (type == 1)
    for (i = 0; i < argc - 2; ++i)
      printf("%d ", ((int *)data)[i]);
  else
    for (i = 0; i < argc - 2; ++i)
      printf("%c ", data[i]);
  if (type)
    free(data);

  return 0;
}