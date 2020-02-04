#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "list.h"

void list_insertion_sort_recursive(list_t *list);

void list_insertion_sort(list_t *list);

void array_insertion_sort(int *a, int size);
#endif