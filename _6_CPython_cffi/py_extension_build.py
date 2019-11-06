#!/usr/bin/env python3

from cffi import FFI

ffi = FFI()


ffi.cdef(
r"""
    // declarations that are shared between Python and C
    struct BinarySearchNode {
        struct BinarySearchNode * left;
        struct BinarySearchNode * right;
        int value;
    };

    struct BinarySearchNode * node_new( int init_value);
    void node_add( struct BinarySearchNode * node, int new_value);
    void node_free( struct BinarySearchNode * node);
    int node_search( struct BinarySearchNode * node, int search_value);
""")

ffi.set_source("_bst",  # name of the output C extension
               r"""  
                    #include "bst/node.h"
                """,
               sources=['bst/node.c'])

if __name__ == "__main__":
    ffi.compile(verbose=True)
