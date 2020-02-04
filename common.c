#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include "common.h"
#include "list.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define HIGHLIGHT "\x1B[42;37;1m"
#define endl 78
#define SPACES 3

int *rand_int_array(int size, int seed)
{
    srand(seed);

    int *array = malloc(sizeof(int)*size);
    for (int i=0; i < size; i++) {
        array[i] = rand() % 100;
    }

    return array;
}
 
list_t *rand_int_list(int size, int seed) 
{
    list_t *list = list_create(compare_ints);
    if (list == NULL) {
        printf("Could not create list in rand_int_list\n");
        return NULL;
    }

    srand(seed);

    int *val;
    for (int i=0; i < size; i++) {
        val = malloc(sizeof(int));
        if (val == NULL) goto error;

        *val = rand() % 100;
        list_pushback(list, val);
    }

    return list;

error:
    printf("Could not allocate memory for new integer in rand_int_list\n");
    list_destroy(list, free);
    return NULL; 
}

list_t *seq_int_list(int size) 
{
    list_t *list = list_create(compare_ints);
    if (list == NULL) {
        printf("Could not create list in rand_int_list\n");
        return NULL;
    }

    int *val;
    for (int i = 1; i < size+1; i++) {
        val = malloc(sizeof(int));
        if (val == NULL) goto error;

        *val = i;
        list_pushback(list, val);
    }

    return list;

error:
    printf("Could not allocate memory for new integer in rand_int_list\n");
    list_destroy(list, free);
    return NULL; 
}

int **create_matrix(int N, int M, int fill)
{
    int **matrix;
    matrix = malloc(N * sizeof(int*));
    if (matrix == NULL) goto error;

    int i, j;
    for (i = 0; i < N; i++) {
        matrix[i] = malloc(M * sizeof(int));
        if (matrix[i] == NULL) goto error;
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            matrix[i][j] = fill;
        }
    }

    // printf("Created matrix with dimensions [%d, %d]\n", N, M);
    return matrix;
error:
    printf("Could not allocate memory for matrix in create_matrix\n");
    exit(0);
}

void destroy_matrix(int **matrix, int N, int M)
{
    for (int i = 0; i < N; ++i) {
        free(matrix[i]);
    }

    free(matrix);
}

void print_int_array(int *array, int size)
{
    for (int i=0; i<size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}   

void print_int_array_matrix(int *a, int size, int *highlights, int n)
{
    printf(GRN);

    int i, j, k;

    i = j = k = 0;

    while (i < size) {
        if (j == 0) printf("\n");
        
        if (a[i] < 10) printf(" ");

        if (i == highlights[k]) {
            printf(HIGHLIGHT "%d" RESET GRN " ", a[i]);
            k++;
        } else {
            printf("%d ", a[i]);
        } 

        i++;
        j = (j+1) % endl;
    }

    printf(RESET);
    printf("\033[%d;%dH", 0, 0);
    return;
}

void print_int_list_matrix(list_t *list, int highlight)
{
    list_iter_t *iter;
    iter = list_createiter(list);
    if (iter == NULL) goto error;
    
    int *elem;
    int i = 0;
    int x = 0;

    printf(GRN);
    while (elem = list_next(iter)) {
        x++;
        if (i == 0) 
            printf("\n");
       
        if (*elem < 10) 
            printf(" ");
        
        if (x == highlight)
            printf(HIGHLIGHT "%d" RESET GRN " ", *elem);
        else 
            printf("%d ", *elem); 
        
        i = (i+1) % endl;
    }

    printf(RESET);
    printf("\033[%d;%dH", 0, 0);
    free(iter);

    return;
error:
    printf("Could not allocate memory for list_iter_t in print_list\n");
    return;
}

void print_int_list(list_t *list)
{
    list_iter_t *iter;
    iter = list_createiter(list);
    if (iter == NULL) goto error;
    
    int *elem;
    int i = 0;

    while (elem = list_next(iter)) {
        if (i == 0) 
            printf("\n");
       
        if (*elem < 10) 
            printf(" ");
                
        printf("%d ", *elem); 
        
        i = (i+1) % 40;
    }

    printf("\n");
    free(iter);
    return;
error:
    printf("Could not allocate memory for list_iter_t in print_list\n");
    return;
}

void print_matrix(int **matrix, int N, int M)
{
    printf("[%d, %d]\n", N, M);
    int val, i, j;

    for (i = 0; i < N; i++) {
        printf("   ");
        for (j = 0; j < M; j++) {
            val = matrix[i][j];

            if (val == 23) {
                printf("\n\nVal is 23\n\n");
                exit(0);
            }
            if (val < 10) 
                printf(" ");
            printf(" %d", val);
            
        }
        printf("\n");
    }
    // int val;
    // for (int i = 0; i < N; i++) {
    //     printf("   ");
    //     for (int j = 0; j < M; j++) {
    //         val = matrix[i][j];
    //         if (val < 10)
    //             printf(" ");
    //         printf("  %d", val);
    //     }
    //     printf("\n");
    //}
}

int comp_n_swap_matrix(list_t *list, node_t *node, int highlight)
{
    if (node == NULL) 
        return 0;

    if (node->next == NULL)
        return 0;

    if (list->cmpfunc(node->elem, node->next->elem) > 0) {
        list_swapnext(list, node);
        print_int_list_matrix(list, highlight);
        return 1;
    } else {
        return 0;
    }
}

int list_assert_sorted(list_t *list)
{
    for (node_t *node = list->head; node->next != NULL; node = node->next) {
        if (list->cmpfunc(node->elem, node->next->elem) > 0)
            return 0;
    }
    return 1;
}

int array_assert_sorted(int *a, int size)
{
    for (int i = 1; i < size-1; i++) {
        if (a[i] > a[i+1]) 
            return 0;
    }
    return 1;
}

/*
 * 3 - 2 = 1
 */
inline int compare_ints(void *a, void *b)
{
   return *(int*)a - *(int*)b;
}

inline int compare_strings(void *a, void *b) 
{
    return strcmp(a, b);
}