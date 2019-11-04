#ifndef __TREE_H__
#define __TREE_H__

typedef struct _binary_tree_node {
    struct _binary_tree_node * left;
    struct _binary_tree_node * right;
    int value;

} BSTNode;

BSTNode* node_new( int new_value);

BSTNode* node_get_left(BSTNode* node);
BSTNode* node_get_right(BSTNode* node);
int node_get_value(BSTNode* node);

BSTNode* tree_new( int ncount, int init[]);

void tree_add( BSTNode * node, int new_value);

int tree_search( BSTNode * node, int search_value);


#endif // #ifndef __TREE_H__
