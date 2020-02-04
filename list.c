/*
 * Implementation for doubly linked list by Naphat Amundsen. 
 */
#include<stdio.h>
#include<stdlib.h>
#include "list.h"

list_t *list_create(cmpfunc_t cmpfunc) 
{
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->size = 0;
    list->cmpfunc = cmpfunc;

    return list;
}

int list_size(list_t *list)
{
    return list->size;
}

static node_t *node_create(void *elem)
{
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        return NULL;
    }

    node->elem = elem;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

void list_pushfront(list_t *list, void *elem)
{
    node_t *node = node_create(elem);
    if (node == NULL) {
        printf("Could not allocate new node in list_pushfront");
        return;
    }

    if (list_size(list) == 0) {
        list->head = node; 
        list->tail = node;
        list->size++;        
        return;
    }

    node->next = list->head;
    list->head->prev = node;
    list->head = node; 
    list->size++;
}

void list_pushback(list_t *list, void *elem)
{
    node_t *node = node_create(elem);
    if (node == NULL) {
        printf("Could not allocate new node in list_pushback");
        return;
    }

    if (list_size(list) == 0) {
        list->head = node; 
        list->tail = node; 
        list->size++;
        return;
    }

    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node; 
    list->size++;
}

void *list_popfront(list_t *list)
{
    if (list->size == 0) {
        printf("list_popfront: list is empty");
        return NULL;
    } 

    void *elem = list->head->elem;
    node_t *old_head = list->head;

    if (list->size > 1) {
        list->head = old_head->next;
        list->head->prev = NULL;
    } else {
        list->head = NULL;
        list->tail = NULL;
    }

    list->size--;
    free(old_head); 
    return elem;
}

node_t *node_popfront(node_t **head)
{
    if (*head == NULL) 
        return NULL;

    if ((*head)->next == NULL)
        return *head;

    node_t *temp;

    temp = (*head);
    (*head) = (*head)->next;

    temp->next = NULL;
    (*head)->prev = NULL;
    return temp;
}

void *list_popback(list_t *list)
{
    if (list->size == 0) {
        printf("list_popback: list is empty");
        return NULL;
    } 

    void *elem = list->tail->elem;
    node_t *old_tail = list->tail;

    if (list->size > 1) {
        list->tail = old_tail->prev;
        list->tail->next = NULL;
    } else {
        list->tail = NULL;
        list->head = NULL;
    }

    list->size--;
    free(old_tail); 
    return elem;
}

void list_swapnext(list_t *list, node_t *node)
{
    node_t *temp = node->next;
    node->next = temp->next;
    temp->prev = node->prev;

    node->prev = temp;
    temp->next = node;

    if (temp->prev != NULL) 
        temp->prev->next = temp;
    else
        list->head = temp;

    if (node->next != NULL) 
        node->next->prev = node; 
    else 
        list->tail = node; 
}

void node_merge(node_t *left_tail, node_t *right_head)
{
    left_tail->next = right_head;
    right_head->prev = left_tail;
}

node_t *node_splithalf(node_t *node)
{
    if ((node == NULL) || (node->next == NULL))
        return NULL;

    node_t *slow, *fast;

    slow = node;
    fast = node->next;
    
    while ((fast != NULL) && (fast->next != NULL)) {
        slow = slow->next;
        fast = fast->next->next;
    }

    fast = slow->next;
    fast->prev = NULL;
    slow->next = NULL;

    return fast;
}

void list_destroy(list_t *list, free_elem_t func)
{
    while(list_size(list) > 0) {
        func(list_popfront(list));
    }
    free(list);
}

list_iter_t *list_createiter(list_t *list)
{
    list_iter_t *iter = malloc(sizeof(list_iter_t));
    iter->current = list->head;
    iter->list = list;
    return iter;
}

void *list_next(list_iter_t *iter)
{
    if (iter->current == NULL) {
        return NULL;
    }
    
    void *elem = iter->current->elem;
    iter->current = iter->current->next;
    return elem; 
}

void list_resetiterator(list_iter_t *iter)
{
    iter->current = iter->list->head;
}

void list_destroyiter(list_iter_t *iter)
{
    free(iter);
}










