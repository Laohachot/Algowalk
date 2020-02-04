#ifndef LIST_H
#define LIST_H

/*
 * Custom types
 */ 
typedef int (*cmpfunc_t)(void*, void*);
typedef void (*free_elem_t)(void*);

// Has to be like this
typedef struct node node_t;
struct node {
    void *elem;
    node_t *next;
    node_t *prev;
};

typedef struct list {
    node_t *head;
    node_t *tail;
    cmpfunc_t cmpfunc;
    int size;
} list_t;

typedef struct list_iter {
    node_t *current;
    list_t *list;
} list_iter_t;

/*
 * Creates a list in heap and returns a pointer to the list. 
 */
list_t *list_create(cmpfunc_t cmpfunc);

/*
 * Returns the size of a given list.
 */
int list_size(list_t *list);

/*
 * Inserts element at the front of a given list. 
 * This increases the list's size by 1.
 */
void list_pushfront(list_t *list, void *elem);

/*
 * Inserts element at the back of a given list. 
 * This increases the list's size by 1.
 */
void list_pushback(list_t *list, void *elem);

/*
 * Merges two lists given a tail and head node.
 * the head will be connected to the tail.
 */
void node_merge(node_t *left_tail, node_t *right_head);

/*
 * Pops first element of the list and returns a pointer 
 * to the element. This reduces the list's size by 1.
 * Returns NULL if list is empty.  
 */
void *list_popfront(list_t *list);

/*
 * Pops first node of a linked list given
 * the head node. Intended use for mergesort.
 */
node_t *node_popfront(node_t **head);

/*
 * Pops last element of the list and returns a pointer
 * to the element. This reduces the list's size by 1.
 * Returns NULL if list is empty.
 */
void *list_popback(list_t *list);

/*
 * Swaps given node with succeeding node.
 */
void list_swapnext(list_t *list, node_t *node);


/*
 * Splits a list in half given its head node, returns 
 * pointer to last half.
 */
node_t *node_splithalf(node_t *node);

/*
 * Destroys a given list by freeing the list its elements. 
 */
void list_destroy(list_t *list, free_elem_t func);

/*
 * Returns an iterator to the first element in a given list. 
 */
list_iter_t *list_createiter(list_t *list);

/*
 * Iterates give iterator once towards tail.
 * Returns the element that the iterator was 
 * pointing to before that iteration. 
 */
void *list_next(list_iter_t *iter);

/*
 * Makes given list iterator return back to 
 * head
 */
void list_resetiterator(list_iter_t *iter);

/*
 * Frees a given list iterator.
 */
void list_destroyiter(list_iter_t *iter);


#endif