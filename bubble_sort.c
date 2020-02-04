#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"
#include "bubble_sort.h"
#include "list.h"

void list_bubble_sort(list_t *list)
{
    int sorted, i;
    node_t *node;

    i = -1;
    node = list->head;
    while (node) {
        i++;
        if (comp_n_swap_matrix(list, node, i)) {
            node = list->head;
            i = 0;
        } else {
            node = node->next;
        }
    }
}


void list_hack_sort(list_t *list)
{
    node_t *heads[100] = {}; // Initialize array with NULLs
    node_t *tails[100] = {};
    node_t *current;
    int *key, i;


    // Organize
    for (current = list->head; current != NULL; current = current->next) {
        key = current->elem;

        if (heads[*key] == NULL) {
            heads[*key] = current;
        } else {
            tails[*key]->next = current;
        }

        current->prev = tails[*key];
        tails[*key] = current;
    }

    // Get start of sorted list
    i = 0;
    while (heads[i] == NULL) {++i;};
    list->head = heads[i];
    list->tail = tails[i];

    ++i;
    while (i <= 99) {
        while (heads[i] == NULL && i <= 99) {++i;};
        if (heads[i] == NULL) break;
        
        node_merge(list->tail, heads[i]);
        list->tail = tails[i];

        list->tail->next = NULL;
        print_int_list_matrix(list, i*2);
        usleep(5000);
        
        ++i;
    }

}
