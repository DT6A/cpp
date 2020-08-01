#include <stdlib.h>  
#include <string.h>
#include <assert.h>

#include "mergesort.h"


void copy(char *dst, char *src, size_t el_size)
{
  assert(dst != NULL && src != NULL);

  size_t i;

  for (i = 0; i < el_size; ++i)
    *(dst + i) = *(src + i);
}

void swap(char *a, char *b, size_t el_size)
{
  char *tmp = (char *)malloc(el_size);

  copy(tmp, a, el_size);
  copy(a, b, el_size);
  copy(b, tmp, el_size);

  free(tmp);
}

// Merges two arrays and puts result into arr1
void merge(void *arr1, void *arr2, size_t n1, size_t n2, size_t el_size, int (*cmp)(const void *e1, const void *e2))
{
  assert(arr1 != NULL && arr2 != NULL && cmp != NULL);

  char *tmp = (char *)malloc((n1 + n2) * el_size);
  assert(tmp != NULL);

  size_t i = 0, j = 0, k = 0;
  
  while (i < n1 && j < n2)
  {
    if (cmp(arr1 + el_size * i, arr2 + el_size * j) > 0)
      copy(tmp + k * el_size, arr2 + el_size * j, el_size), ++j;
    else
      copy(tmp + k * el_size, arr1 + el_size * i, el_size), ++i;
    ++k;
  }

  while (i < n1)
    copy(tmp + k * el_size, arr1 + el_size * i, el_size), ++i, ++k;

  while (j < n2)
    copy(tmp + k * el_size, arr2 + el_size * j, el_size), ++j, ++k;

  for (i = 0; i < n1 + n2; ++i)
    copy(arr1 + i * el_size, tmp + i * el_size, el_size);

  free(tmp);
}

void mergesort(void *arr, size_t n, size_t el_size, int (*cmp)(const void *e1, const void *e2))
{
  assert(arr != NULL && cmp != NULL);

  if (n == 1)
    return;

  mergesort(arr, n / 2, el_size, cmp);
  mergesort(arr + n / 2 * el_size, n - n / 2, el_size, cmp);

  merge(arr, arr + n / 2 * el_size, n / 2, n - n / 2, el_size, cmp);
}