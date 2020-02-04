#ifndef COMMON_H
#define COMMON_H

#include "list.h"

int *rand_int_array(int size, int seed);

void print_int_array(int *array, int size);

void print_int_array_matrix(int *a, int size, int *highlights, int n);

void print_int_list_matrix(list_t *list, int highlight);

void print_int_list(list_t *list);

void print_matrix(int **matrix, int N, int M);

list_t *rand_int_list(int size, int seed); 

list_t *seq_int_list(int size); 

int **create_matrix(int n, int m, int fill);

void destroy_matrix(int **matrix, int N, int M);

int compare_ints(void *a, void *b);

int compare_strings(void *a, void *b);

/*
 * Compares given node to succeeding node. 
 * If suceeding node is larger, then a swap
 * operation is invoked, and the function
 * returns 1. This function will print a lot 
 * of stuff so its looks cool.
 */
int comp_n_swap_matrix(list_t *list, node_t *node, int highlight);

int list_assert_sorted(list_t *list);

int array_assert_sorted(int *a, int size);


#endif