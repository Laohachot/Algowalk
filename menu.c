#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "common.h"
#include "list.h"
#include "insertion_sort.h"
#include "bubble_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "simple_bst.h"
#include "rb_bst.h"
#include "heap_sort.h"

#define ERASE "\033[2J" 

typedef void (*listsorter_t)(list_t *);
typedef void (*arraysorter_t)(int *, int);

void clear() 
{
    system("clear");
    printf(ERASE);
}

void keypause()
{
    int c;
    while(c = getchar() != '\n' && c != EOF);
    printf("Press enter to continue\n");
    getchar();
    clear();
}

void run_array_algo(int *array, int size, arraysorter_t sortfunc)
{
    clear();

    sortfunc(array, size);

    clear();

    int a[1] = {-1};

    printf("\nResult:\n");
    print_int_array_matrix(array, size, a, 1);

    if (array_assert_sorted(array, size))
        printf("Assert sort: Pass\n");
    else 
        printf("Assert sort: Fail\n");

    keypause();
}

void array_algos(int num_elements)
{
    clear();

    int choice, *ints;
    
    ints = rand_int_array(num_elements, 1337);
    
    printf("Generated array of %d elements\n", num_elements);
    printf("1. Quick sort\n");
    printf("2. Heap sort\n");
    printf("3. Selection sort\n");
    printf("4. Insertion sort\n");

    scanf("%d", &choice);

    switch (choice) {
        case 1:
            run_array_algo(ints, num_elements, array_quick_sort);
            break;
        
        case 2:
            run_array_algo(ints, num_elements, array_heap_sort);
            break;

        case 3:
            run_array_algo(ints, num_elements, selection_sort);
            break;
        
        case 4:
            run_array_algo(ints, num_elements, array_insertion_sort);
            break;

        default:
            break;
    }

    free(ints);
}

void run_list_algo(list_t *list, listsorter_t sortfunc)
{
    clear();

    sortfunc(list);

    clear();

    printf("\nResult:\n");
    print_int_list_matrix(list, -1);
 
    if (list_assert_sorted(list))
        printf("Assert sort: Pass\n");
    else 
        printf("Assert sort: Fail\n");

    keypause();
}

void list_algos(int num_elements)
{
    clear();

    int choice;
    list_t *ints; 
    
    ints = rand_int_list(num_elements, 1337);
    
    printf("Generated list of %d elements\n", num_elements);
    printf("1. Insertion sort\n");
    printf("2. Bubble sort\n");
    printf("3. Merge sort\n");
    printf("4. Hack sort\n");

    scanf("%d", &choice);

    switch (choice) {
        case 1:
            run_list_algo(ints, list_insertion_sort);
            break;
        case 2:
            run_list_algo(ints, list_bubble_sort);
            break;
        case 3:
            run_list_algo(ints, list_merge_sort);
            break;
        case 4:
            run_list_algo(ints, list_hack_sort);
        default:
            break;
    }

    list_destroy(ints, free);
}

void run_sbstree_algo(list_t *list)
{
    clear();
    stnode_t *root = sbst_fromlist(list);

    printf("List: ");
    print_int_list(list);

    // printf("\n");

    printf("Tree: \n");
    sbst_print(root);

    printf("Fancyprint: \n");
    sbst_fancyprint(root);

    keypause();
}

void run_rbtree_algo(list_t *list)
{
    clear();
    rbnode_t *root = rbt_fromlist(list);

    printf("List: ");
    print_int_list(list);

    printf("Tree: \n ");
    rbt_print(root);

    printf("Fancyprint: \n");
    rbt_fancyprint(root);

    _rbt_destroy(root);
    free(root);
    keypause();
}

void tree_algos(int num_elements)
{
    clear();

    int choice;
    // list_t *ints = rand_int_list(num_elements, 1337);
    list_t *ints = seq_int_list(num_elements);


    printf("Generated a list of %d integers to be inserted in a\n", num_elements);
    printf("1. Simple Binary Search Tree\n");
    printf("2. Red Black Binary Search Tree\n");

    scanf("%d", &choice);

    switch (choice) {
        case 1: 
            run_sbstree_algo(ints);
            break;
        case 2: 
            run_rbtree_algo(ints);
            break;
        default:
            break;
    }

    list_destroy(ints, free);
}

int main(int argc, char **argv)
{
    int num_elements, choice, active;

    clear();
    
    num_elements = atoi(argv[1]);    

    active = 1;
    while (active) {
        printf("1. Array algorithms\n");
        printf("2. Linked list algorithms\n");
        printf("3. Binary tree algorithms\n");
        printf("0. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                array_algos(num_elements);
                break;
            
            case 2:
                list_algos(num_elements);
                break;
            
            case 3:
                tree_algos(num_elements);
                break;

            default:
                active = 0;
                break;    
        }
    }
}



