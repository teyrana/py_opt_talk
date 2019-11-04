#include <stdlib.h>

// #include <Python/Python.h>

#include "tree.h"

// static PyMethodDef BinarySearchTreeModule_StaticMethods[] = {
//     { "node_new", node_new, 1, "create a new node" },
//     { "tree_new", tree_new, 2, "create a new tree" },
//     { "tree_add", tree_add, 2, "add a node to this tree" },
//     { "tree_search", tree_search, 2, "search this tree for a particular value" },
//     { NULL, NULL, 0, NULL }
// };

BSTNode* node_new( int init_value){
    BSTNode * root = malloc(sizeof(BSTNode));
    root->value = init_value;
    root->left = NULL;
    root->right = NULL;
    return root;
}

int node_get_value(BSTNode* node){
    return node->value;
}

BSTNode* node_get_left(BSTNode* node){
    return node->left;
}
BSTNode* node_get_right(BSTNode* node){
    return node->right;
}

BSTNode* tree_new( int ncount, int init_values[]){
    // ignore null check; ignore bounds check
    BSTNode * root = node_new( init_values[0] );

    for( int i=0; i < ncount; ++i ){
	 int value = init_values[i];
	 tree_add(root, value);
    }
    return root;
}

void tree_add( BSTNode * node, int new_value){
    // ignore null-case-check
    if( new_value != node->value ){
        if( new_value < node->value ){
            if( NULL == node->left ){
                node->left = node_new(new_value);
            }else{
                tree_add(node->left, new_value);
            }
	}else{
	    if( NULL == node->right ){
		node->right = node_new(new_value);
	    }else{
		tree_add(node->right, new_value);
	    }
	}
    }
}

int tree_search( BSTNode * node, int search_value){
    // ignore null check
    if( NULL == node ){
        return -1;
    }else if( search_value == node->value ){
        return node->value;
    }else if( (search_value < node->value) && (NULL != node->left) ){
        return tree_search(node->left, search_value);
    }else if( (search_value > node->value) && (NULL != node->right) ){
        return tree_search(node->right, search_value);
    }
    return -1;
}

