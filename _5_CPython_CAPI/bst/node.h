#ifndef __NODE_H__
#define __NODE_H__

typedef struct _binary_tree_node {
    struct _binary_tree_node * left;
    struct _binary_tree_node * right;
    int value;
} BinarySearchNode;

BinarySearchNode* node_new( int init_value);

void node_add( BinarySearchNode * node, int new_value);

void node_free( BinarySearchNode* node);

int node_search( BinarySearchNode * node, int search_value);


#endif  // #ifndef __NODE_H__