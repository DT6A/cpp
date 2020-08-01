#pragma once

#include <stddef.h> 

void copy(char *dst, char *src, size_t el_size);
void swap(char *a, char *b, size_t el_size);
void merge(void *arr1, void *arr2, size_t n1, size_t n2, size_t el_size, int (*cmp)(const void *e1, const void *e2));
void mergesort(void *arr, size_t n, size_t el_size, int (*cmp)(const void *e1, const void *e2));