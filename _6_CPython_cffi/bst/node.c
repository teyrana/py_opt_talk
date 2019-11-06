#include "stdlib.h"

#include "node.h"

struct BinarySearchNode * node_new( int init_value){
    struct BinarySearchNode * root = malloc(sizeof(struct BinarySearchNode));
    root->value = init_value;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void node_add( struct BinarySearchNode * node, int new_value){
    // ignore null-case-check
    if( new_value != node->value ){
        if( new_value < node->value ){
            if( NULL == node->left ){
                node->left = node_new(new_value);
            }else{
                node_add(node->left, new_value);
            }
        }else{
            if( NULL == node->right ){
                node->right = node_new(new_value);
            }else{
                node_add(node->right, new_value);
            }
        }
    }
}

void node_free( struct BinarySearchNode* node){
    if( NULL != node->left ){
        node_free(node->left);
        node->left = NULL;
    }
    if( NULL != node->right ){
        node_free(node->right);
        node->right = NULL;
    }
    free(node);
}


int node_search( struct BinarySearchNode * node, int search_value){
    // ignore null check
    if( NULL == node ){
        return -1;
    }else if( search_value == node->value ){
        return node->value;
    }else if( (search_value < node->value) && (NULL != node->left) ){
        return node_search(node->left, search_value);
    }else if( (search_value > node->value) && (NULL != node->right) ){
        return node_search(node->right, search_value);
    }
    return -1;
}

