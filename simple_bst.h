#ifndef SIMPLE_BST_H
#define SIMPLE_BST_H

# include "list.h"

typedef struct stnode stnode_t;

struct stnode {
    stnode_t *left;
    stnode_t *right;
    int key;
};

stnode_t *sbst_newnode(int key);

void sbst_insert(stnode_t *root, int key);

int sbst_search(stnode_t *root, int key);

void sbst_print(stnode_t *root);

void sbst_pprint(stnode_t *root);

void sbst_fancyprint(stnode_t *root);

stnode_t *sbst_fromlist(list_t *list);

#endif