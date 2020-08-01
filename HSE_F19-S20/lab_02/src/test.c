#include <stdio.h>
#include <string.h>

#include "str.h"
#include "test_str.h"

int main(void)
{
  test_len();
  printf("Len passed\n");
  test_cat();
  printf("Cat passed\n");
  test_cpy();
  printf("Cpy passed\n");
  test_cmp();
  printf("Cmp passed\n");
  
  return 0;
}