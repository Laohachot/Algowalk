#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>

#include "rb_bst.h"
#include "common.h"

rbnode_t *rbt_newnode(rbnode_t *parent, int key)
{
    rbnode_t *new = malloc(sizeof(rbnode_t));
    if (new == NULL) goto error;

    new->color = RED;
    new->parent = parent;
    new->key = key;
    new->left = NULL;
    new->right = NULL;
    return new;
error:
    printf("Failed to allocate in rbt_newnode\n");
    exit(0);
}

static rbnode_t *parent(rbnode_t *node)
{
    if (node == NULL) return NULL;
    return node->parent;
}

static rbnode_t *grandparent(rbnode_t *node)
{
    rbnode_t *p = parent(node);
    if (p == NULL) return NULL;
    return parent(p);
}

static rbnode_t *sibling(rbnode_t *node)
{
    rbnode_t *p = parent(node);
    if (p == NULL) return NULL;
    
    if (node == p->left) 
        return p->right; 
    else
        return p->left;
}

static rbnode_t *uncle(rbnode_t *node)
{
    rbnode_t *p, *g;
    p = parent(node);
    g = grandparent(node);

    if (g == NULL) 
        return NULL;
    else 
        return sibling(p);
}

void rotate_left(rbnode_t *node, rbnode_t **rootp) {
    rbnode_t *nnew = node->right;
    rbnode_t *p = parent(node);
    
    assert(nnew != NULL); // since the leaves of a red-black tree are empty, they cannot become internal nodes
    
    node->right = nnew->left; 
    nnew->left = node;
    node->parent = nnew;
    
    // handle other child/parent pointers
    if (node->right != NULL)
        node->right->parent = node;
    if (p != NULL) // initially node could be the root
    {
        if (node == p->left)
            p->left = nnew;
        else if (node == p->right) // if (...) is excessive
            p->right = nnew;
    }
    nnew->parent = p;

    if (parent(nnew) == NULL) {
        *rootp = nnew;
    } 
}

void rotate_right(rbnode_t *node, rbnode_t **rootp) {
    rbnode_t *nnew = node->left;
    rbnode_t *p = parent(node);

    assert(nnew != NULL); // since the leaves of a red-black tree are empty, they cannot become internal nodes
    
    node->left = nnew->right;
    nnew->right = node;
    node->parent = nnew;
    
    // handle other child/parent pointers
    if (node->left != NULL)
     node->left->parent = node;
    if (p != NULL) // initially node could be the root
    {
     if (node == p->left)
      p->left = nnew;
     else if (node == p->right) // if (...) is excessive
      p->right = nnew;
    }
    nnew->parent = p;

    if (parent(nnew) == NULL) 
        *rootp = nnew;
}

static void case4_step2(rbnode_t *current, rbnode_t **rootp)
{
    rbnode_t *p, *gp;

    p = parent(current);
    gp = grandparent(current);

    if (current == p->left) {
        rotate_right(gp, rootp);
    } else {
        rotate_left(gp, rootp);
    } 
    
    p->color = BLACK;
    gp->color = RED;
}

static void case4_step1(rbnode_t *current, rbnode_t **rootp)
{
    rbnode_t *p, *gp;

    p = parent(current);
    gp = grandparent(current);
 
    // printf("p = %p\n", p);
    // printf("gp = %p\n", gp);

    if (current == p->right && p == gp->left) {
        rotate_left(p, rootp);
        current = current->left;
    } else if (current == p->left && p == gp->right) {
        rotate_right(p, rootp);
        current = current->right;
    }

    case4_step2(current, rootp);
}

static void _rbt_fixer(rbnode_t *current, rbnode_t **rootp)
{
    static int i = -1;
    i++;
    // printf("Parent = %p, %d\n", parent(current), i);
    
    if (parent(current) == NULL) {
        // Case 1: Current is root
        current->color = BLACK;
    } else if (parent(current)->color == BLACK) {
        // Case 2: Current's parent is BLACK, all is well
        return;
    } else if (uncle(current) != NULL && uncle(current)->color == RED) {
        // Case 3: Current's uncle is also RED, must recolor
        parent(current)->color = uncle(current)->color = BLACK;
        grandparent(current)->color = RED;

        // After fixing local stuff, move upwards.
        _rbt_fixer(grandparent(current), rootp);
    } else {
        // Case 4: Last case, two consequtive red nodes and red uncle
        case4_step1(current, rootp);
    }
    
}

static rbnode_t *_inserter(rbnode_t *node, rbnode_t *new, rbnode_t *parent)
{
    if (node == NULL) {
        new->parent = parent; 
        return new; 
    }

    if (node->key >= new->key) 
        node->left = _inserter(node->left, new, node);
    else
        node->right = _inserter(node->right, new, node);

    return node; 
}

rbnode_t *rbt_insert(rbnode_t *root, int key)
{
    rbnode_t *new = rbt_newnode(NULL, key); 
    _inserter(root, new, NULL);
    
    _rbt_fixer(new, &root);

    return root;
}

rbnode_t *rbt_fromlist(list_t *list)
{
    list_iter_t *iter; 
    int *key;

    iter = list_createiter(list);
    
    rbnode_t *root = rbt_newnode(NULL, (*(int*)list_next(iter)));
    root->color = BLACK;

    while (key = list_next(iter)) {
        root = rbt_insert(root, *key);
        printf("\033[0;0H");
        printf("Inserted %d\n\n", *key);
        rbt_fancyprint(root);
        usleep(100000);
    }

    list_destroyiter(iter);
    return root;
}

void _rbt_destroy(rbnode_t *node)
{
    if (node == NULL) return;

    _rbt_destroy(node->left);

    if (node->left != NULL) 
        free(node->left);

    _rbt_destroy(node->right);

    if (node->right != NULL)
        free(node->right);
}

static void _get_depth(rbnode_t *node, int currdepth, int *depthptr)
{
    if (node == NULL) return;

    if (*depthptr < currdepth) 
        *depthptr = currdepth;

    _get_depth(node->left, currdepth+1, depthptr);
    _get_depth(node->right, currdepth+1, depthptr);
}

static void _get_leftwidth(rbnode_t *node, int currwidth, int *widthpr)
{
    if (node == NULL) return;

    if (currwidth > *widthpr) ++(*widthpr);
    _get_leftwidth(node->left, currwidth+1, widthpr);
    _get_leftwidth(node->right, currwidth-1, widthpr);
}

static void _get_rightwidth(rbnode_t *node, int currwidth, int *widthpr)
{
    if (node == NULL) return;

    if (currwidth > *widthpr) ++(*widthpr);
    _get_rightwidth(node->right, currwidth+1, widthpr);
    _get_rightwidth(node->left, currwidth-1, widthpr);
}

static void _set_printmatrix(rbnode_t *node, int d, int w, int adjustment, int **matrix)
{
    if (node == NULL) return;

    matrix[d][w] = node->key;

    _set_printmatrix(node->left, d+1, w-adjustment/2-1, adjustment/2, matrix);
    _set_printmatrix(node->right, d+1, w+adjustment/2+1, adjustment/2, matrix);
}

static void compact_setprintmatrix(rbnode_t *node, int d, int w, int left_adjustment, int right_adjustment, int **matrix)
{
    if (node == NULL) return;

    matrix[d][w] = node->key;

    _set_printmatrix(node->left, d+1, w-left_adjustment/2-1, left_adjustment/2, matrix);
    _set_printmatrix(node->right, d+1, w+right_adjustment/2+1, right_adjustment/2, matrix);
    
}

// static void _set_printmatrix(rbnode_t *node, int d, int w, int adjustment, int **matrix)
// {
//     if (node == NULL) return;

//     matrix[d][w] = node->key;

//     _set_printmatrix(node->left, d+1, w-adjustment/2-1, adjustment/2, matrix);
//     _set_printmatrix(node->right, d+1, w+adjustment/2+1, adjustment/2, matrix);
// }

void rbt_fancyprint(rbnode_t *root)
{

    int left_depth, right_depth;
    left_depth = right_depth = 1;

    if (root->left != NULL) 
        _get_depth(root->left, 1, &left_depth);
    else 
        left_depth = 0;
    
    if (root->right != NULL)
        _get_depth(root->right, 1, &right_depth);
    else 
        right_depth = 0;

    // 1. Get dimensions
    int depth = 1;
    _get_depth(root, 1, &depth);

    int leftwidth = 0;
    _get_leftwidth(root, 0, &leftwidth);

    int rightwidth = 0;
    _get_rightwidth(root, 0, &rightwidth);

    int width = leftwidth + rightwidth + 1;

    leftwidth = pow(2, left_depth) - 1;
    rightwidth = pow(2, right_depth) - 1;

    printf("d = %d\n", depth);
    printf("ld = %d\n", left_depth);
    printf("rd = %d\n", right_depth);
    printf("lw = %d\n", leftwidth);
    printf("rw = %d\n", rightwidth);
    printf("w = %d\n\n", width);

    width = leftwidth + rightwidth + 1;

    // 2. Get dat matrix
    int **matrix = create_matrix(depth, leftwidth+rightwidth+1, 0);
    // exit(0);

    // 3. Set dat matrix
    compact_setprintmatrix(root, 0, leftwidth, leftwidth, rightwidth, matrix);

    int row, col, next_row, flag, above, below;
    for (row = 0; row < depth; row++) {
        
        // Print a row from the matrix
        for (col = 0; col < width; col++) {
            if (matrix[row][col])
                printf("%3d", matrix[row][col]);
            else
                printf("%*s", 3, "");
        }
        printf("\n");
        
        flag = 0;

        if (row < depth-1) {
            printf("  ");
            // Prints the "tree structure"
            for (col = 0; col < width; col++) {
                above = matrix[row][col];
                below = matrix[row+1][col];

                if ((below && flag == 0) && col < width-1) {
                    printf("___");
                    flag = 1;
                    continue;
                }
                
                if (flag && below) 
                    flag = 0;

                if (flag) {
                    if (above) 
                        printf("|__");
                     else 
                        printf("___");
                } else {
                    printf("   ");
                }
            }
            printf("\n");
        }
    }

    destroy_matrix(matrix, depth, width);
}

static void _printer(rbnode_t *node, int *i)
{
    *i = ((*i) + 1) % 70;
    if (*i == 0) printf("\n");

    if (node == NULL) return;
    _printer(node->left, i);
    printf("%d ", node->key);
    _printer(node->right, i);
}

void rbt_print(rbnode_t *root)
{
    int i = 0;
    _printer(root, &i);
    printf("\n");
}