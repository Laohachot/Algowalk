#ifndef RB_BST_H
#define RB_BST_H

#include "list.h"

typedef struct rbnode rbnode_t;

enum {
    RED,
    BLACK
} color_t;

struct rbnode {
    int color;
    rbnode_t *parent;
    rbnode_t *left;
    rbnode_t *right;
    int key;
};

rbnode_t *rbt_newnode(rbnode_t *parent, int key);

rbnode_t *rbt_insert(rbnode_t *root, int key);

int rbt_search(rbnode_t *root, int key);

void rbt_print(rbnode_t *root);

void rbt_pprint(rbnode_t *root);

void rbt_fancyprint(rbnode_t *root);

rbnode_t *rbt_fromlist(list_t *list);

void _rbt_destroy(rbnode_t *node);

#endif