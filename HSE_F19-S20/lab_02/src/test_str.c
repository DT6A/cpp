#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "test_str.h"
#include "str.h"

void test_cmp(void)
{
  char str[100], str2[100];

  strcpy(str, "qwdq 231 sak lml12"), strcpy(str2, "qwdq123\n 2213sad1qqq31 sak lml12");
  assert((strcmp(str, str2) == 0) == (my_strcmp(str, str2) == 0));
  strcpy(str, ""), strcpy(str2, "");
  assert((strcmp(str, str2) == 0) == (my_strcmp(str, str2) == 0));
  strcpy(str, "\n"), strcpy(str2, "\n");
  assert((strcmp(str, str2) == 0) == (my_strcmp(str, str2) == 0));
  strcpy(str, "hello"), strcpy(str2, "Hello");
  assert((strcmp(str, str2) == 0) == (my_strcmp(str, str2) == 0));
  strcpy(str, "    ;;"), strcpy(str2, "   dw ");
  assert((strcmp(str, str2) == 0) == (my_strcmp(str, str2) == 0));
  strcpy(str, "test test"), strcpy(str2, "test tset");
  assert((strcmp(str, str2) == 0) == (my_strcmp(str, str2) == 0));
 }

void test_cpy(void)
{
  char str[100], str2[100], str_app[100];

  strcpy(str, "qwdq 231 sak lml12"), strcpy(str2, "qwdq 231 sak lml12"), strcpy(str_app, "123214 124 1");
  assert(!strcmp(strcpy(str, str_app), my_strcpy(str2, str_app)));
  strcpy(str, ""), strcpy(str2, ""), strcpy(str_app, "");
  assert(!strcmp(strcpy(str, str_app), my_strcpy(str2, str_app)));
  strcpy(str, "\n"), strcpy(str2, "\n"), strcpy(str_app, "");
  assert(!strcmp(strcpy(str, str_app), my_strcpy(str2, str_app)));
  strcpy(str, "Hello"), strcpy(str2, "Hello"), strcpy(str_app, " world");
  assert(!strcmp(strcpy(str, str_app), my_strcpy(str2, str_app)));
  strcpy(str, "    "), strcpy(str2, "    "), strcpy(str_app, "end");
  assert(!strcmp(strcpy(str, str_app), my_strcpy(str2, str_app)));
  strcpy(str, "test test"), strcpy(str2, "test test"), strcpy(str_app, "passed");
  assert(!strcmp(strcpy(str, str_app), my_strcpy(str2, str_app)));
}

void test_cat(void)
{
  char str[100], str2[100], str_app[100];

  strcpy(str, "qwdq 231 sak lml12"), strcpy(str2, "qwdq 231 sak lml12"), strcpy(str_app, "123214 124 1");
  assert(!strcmp(strcat(str, str_app), my_strcat(str2, str_app)));
  strcpy(str, ""), strcpy(str2, ""), strcpy(str_app, "");
  assert(!strcmp(strcat(str, str_app), my_strcat(str2, str_app)));
  strcpy(str, "\n"), strcpy(str2, "\n"), strcpy(str_app, "");
  assert(!strcmp(strcat(str, str_app), my_strcat(str2, str_app)));
  strcpy(str, "Hello"), strcpy(str2, "Hello"), strcpy(str_app, " world");
  assert(!strcmp(strcat(str, str_app), my_strcat(str2, str_app)));
  strcpy(str, "    "), strcpy(str2, "    "), strcpy(str_app, "end");
  assert(!strcmp(strcat(str, str_app), my_strcat(str2, str_app)));
  strcpy(str, "test test"), strcpy(str2, "test test"), strcpy(str_app, "passed");
  assert(!strcmp(strcat(str, str_app), my_strcat(str2, str_app)));
}

void test_len(void)
{
  char *str;

  str = "  ";
  assert(strlen(str) == my_strlen(str));
  str = "Hello";
  assert(strlen(str) == my_strlen(str));
  str = "\n";
  assert(strlen(str) == my_strlen(str));
  str = "asdkjadljwiqjiojq \n\t\riwe oqw eiioi q w  oeq        w;eq ie";
  assert(strlen(str) == my_strlen(str));
  str = "           ";
  assert(strlen(str) == my_strlen(str));
  str = "test test test test test test test test test test";
  assert(strlen(str) == my_strlen(str));
}