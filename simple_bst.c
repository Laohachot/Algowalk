#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "simple_bst.h"
#include "common.h"

stnode_t *sbst_newnode(int key)
{
    stnode_t *root = malloc(sizeof(stnode_t));
    if (root == NULL) goto error;
    
    root->left = NULL;
    root->right = NULL;
    root->key = key;

    return root;

error:
    printf("Could not allocate new node in sbst_create\n");
    exit(0);
}

static stnode_t *_inserter(stnode_t *node, int key)
{
    if (node == NULL) return sbst_newnode(key);

    if (key <= node->key)
        node->left = _inserter(node->left, key);
    else
        node->right = _inserter(node->right, key);

    return node;
}

void sbst_insert(stnode_t *root, int key)
{
    _inserter(root, key);
}


static int _seeker(stnode_t *node, int key)
{
    if (node == NULL) return 0;

    if (node->key == key) return 1;

    if (key <= node->key)
        return _seeker(node->left, key);
    else
        return _seeker(node->right, key);
}

int sbst_search(stnode_t *root, int key)
{
    return _seeker(root, key);
}

static void _printer(stnode_t *node)
{
    if (node == NULL) return;

    _printer(node->right);
    printf("%d ", node->key);
    _printer(node->left);
}

void sbst_print(stnode_t *root)
{
    _printer(root);
    printf("\n");
}

static void _pprinter(stnode_t *node, int depth)
{
    if (node == NULL) return;

    _pprinter(node->right, depth+1);
    
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    
    printf("%d ", node->key);
    printf("\n");
    _pprinter(node->left, depth+1);
}

void sbst_pprint(stnode_t *root)
{
    _pprinter(root, 0);
    printf("\n");
}

static void _get_depth(stnode_t *node, int currdepth, int *depthptr)
{
    if (node == NULL) return;

    if (*depthptr < currdepth) 
        *depthptr = currdepth;

    _get_depth(node->left, currdepth+1, depthptr);
    _get_depth(node->right, currdepth+1, depthptr);
}

static void _get_leftwidth(stnode_t *node, int currwidth, int *widthpr)
{
    if (node == NULL) return;

    if (currwidth > *widthpr) ++(*widthpr);
    _get_leftwidth(node->left, currwidth+1, widthpr);
    _get_leftwidth(node->right, currwidth-1, widthpr);
}

static void _get_rightwidth(stnode_t *node, int currwidth, int *widthpr)
{
    if (node == NULL) return;

    if (currwidth > *widthpr) ++(*widthpr);
    _get_rightwidth(node->right, currwidth+1, widthpr);
    _get_rightwidth(node->left, currwidth-1, widthpr);
}

static void _set_printmatrix(stnode_t *node, int d, int w, int adjustment, int **matrix)
{
    if (node == NULL) return;
    int w_adjust = w + adjustment;
    matrix[d][w_adjust] = node->key;

    _set_printmatrix(node->left, d+1, w-1, adjustment, matrix);
    _set_printmatrix(node->right, d+1, w+1, adjustment, matrix);
}

void sbst_fancyprint(stnode_t *root)
{

    // 1. Get dimensions
    int depth = 1;
    _get_depth(root, 1, &depth);

    int leftwidth = 0;
    _get_leftwidth(root, 0, &leftwidth);

    int rightwidth = 0;
    _get_rightwidth(root, 0, &rightwidth);

    int width = leftwidth + rightwidth + 1;

    // printf("d = %d\n", depth);
    // printf("lw = %d\n", leftwidth);
    // printf("rw = %d\n", rightwidth);
    // printf("w = %d\n\n", width);

    // 2. Get dat matrix
    int **matrix = create_matrix(depth, width, 0);
    // exit(0);

    // 3. Set dat matrix
    _set_printmatrix(root, 0, 0, leftwidth, matrix);

    int val;
    for (int i = 0; i < depth; i++) {
        printf("   ");
        for (int j = 0; j < width; j++) {
            val = matrix[i][j];
            if (val) {
                if (val < 10)
                    printf(" ");
                printf("  %d", val);
            } else {
                printf("     ");
            }   
        }
        printf("\n");
    }
}

stnode_t *sbst_fromlist(list_t *list)
{
    list_iter_t *iter; 
    int *key;

    iter = list_createiter(list);
    
    stnode_t *root = sbst_newnode((*(int*)list_next(iter)));

    while (key = list_next(iter)) {
        sbst_insert(root, *key);
    }

    list_destroyiter(iter);
    return root;
}
