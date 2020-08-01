#include <assert.h>
#include <stdlib.h>

#include "str.h"

int my_strcmp(const char *s1, const char *s2)
{
  assert(s1 != NULL);
  assert(s2 != NULL);

  while (*s1 != '\0' && *s1 == *s2)
    ++s1, ++s2;
  return *s1 - *s2;
}

char *my_strcpy(char * restrict s1, const char * restrict s2)
{
  char *pointer = s1;

  assert(s1 != NULL);
  assert(s2 != NULL);

  while (*s2 != '\0')
  {
    *pointer = *s2;
    ++pointer;
    ++s2;
  }
  
  *pointer = '\0';
  
  return s1;
}


char *my_strcat(char * restrict s1, const char * restrict s2)
{
  char *pointer = s1 + my_strlen(s1);

  assert(s1 != NULL);
  assert(s2 != NULL);

  while (*s2 != '\0')
  {
    *pointer = *s2;
    ++pointer;
    ++s2;
  }

  *pointer = '\0';

  return s1;
}

size_t my_strlen(const char *s)
{
  size_t len = 0;

  assert(s != NULL);
  
  
  while (*(s + len) != '\0')
    ++len;

  return len;
}