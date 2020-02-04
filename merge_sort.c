#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"
#include "list.h"

static inline node_t *conquerer(node_t *left, node_t *right, cmpfunc_t cmpfunc)
{
    node_t *head, *tail;

    if (cmpfunc(left->elem, right->elem) < 0) {
        head = left;
        left = left->next;
    } else {
        head = right;
        right = right->next;
    }  

    tail = head;    

    while ((left != NULL) && (right != NULL)) {
        if (cmpfunc(left->elem, right->elem) < 0) {
            tail->next = left;
            tail = left;
            left = left->next;
        } else {
            tail->next = right;
            tail = right;
            right = right->next;
        }   
    }

    if (left != NULL) 
        tail->next = left;
    else 
        tail->next = right;

    return head;
}

node_t *_divider(node_t *head, cmpfunc_t cmpfunc)
{
    if ((head == NULL) || (head->next == NULL)) 
        return head;
    
    node_t *righthalf;

    righthalf = node_splithalf(head);
    head = _divider(head, cmpfunc);
    righthalf = _divider(righthalf, cmpfunc);   
    
    list_t *list = list_create(compare_ints);

    head = list->head = conquerer(head, righthalf, cmpfunc); 
    print_int_list_matrix(list, 0);

    usleep(1000);

    free(list);
    return head; 
}

void list_merge_sort(list_t *list)
{
    list->head = _divider(list->head, list->cmpfunc);

    node_t *node, *temp;
    int i = 0;

    temp = NULL;
    for(node = list->head; node != NULL; node = node->next) {
        i++;
        print_int_list_matrix(list, i);
        usleep(200);
        node->prev = temp;
        temp = node;
    }
    list->tail = temp;
}