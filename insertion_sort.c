#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "insertion_sort.h"
#include "list.h"
#include "common.h"

void _insertion_sort(node_t *node, list_t *list, int repeat)
{
    
    if ((node == NULL) || (node->next == NULL)) {
        return;
    }

    if (list->cmpfunc(node->elem, node->next->elem) > 0) {
        list_swapnext(list, node);
        _insertion_sort(node->prev->prev, list, 0);
        _insertion_sort(node, list, 1);
        return;
    } else {
        if (repeat)
            _insertion_sort(node->next, list, 1);
        return;
    }
}

/*
 * Sorts a given list inplace using the recursive
 * insertion sort algorithm. 
 */
void list_insertion_sort_recursive(list_t *list)
{
    if (list_size(list) <= 1) 
        return; 
    
    _insertion_sort(list->head, list, 1);     
}

/*
 * Sorts a given list inplace using the insertion
 * sort algorithm. 
 */
void list_insertion_sort(list_t *list)
{
    node_t *node, *temp;
    int *elem, i, x; // i and x to print cool stuff

    i = -1;
    node = list->head;
    while (node) {
        i++;
        // print_int_list_matrix(list, i);
        if (comp_n_swap_matrix(list, node, i)) {
            x = i;
            temp = node->prev;
            while (temp = temp->prev) {
                if (comp_n_swap_matrix(list, temp, x)) {
                    temp = temp->prev;
                } else {
                    break;
                }
                x--;
            }
        } else {
            node = node->next;
        }
    }
}

/* Function to sort an array using insertion sort*/
void array_insertion_sort(int *a, int size) 
{ 
    int i, key, j; 

    int highlights[1];

    for (i = 1; i < size; i++) { 
        key = a[i]; 
        j = i - 1; 
  
        /* Move elements of a[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while (j >= 0 && a[j] > key) { 
            a[j + 1] = a[j]; 
            j = j - 1;

            highlights[0] = i;
            print_int_array_matrix(a, size, highlights, 1);
        } 
        a[j + 1] = key; 
    } 
}



