#include <stdlib.h>

#include "Python.h"

typedef struct _binary_tree_node {
    struct _binary_tree_node * left;
    struct _binary_tree_node * right;
    int value;
} BinarySearchNode;

typedef struct _binary_search_tree {
    PyObject_HEAD;
    BinarySearchNode * root;
} BinarySearchTree;



BinarySearchNode* node_new( int init_value){
    BinarySearchNode * root = malloc(sizeof(BinarySearchNode));
    root->value = init_value;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void node_add( BinarySearchNode * node, int new_value){
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

void node_free( BinarySearchNode* node){
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


int node_search( BinarySearchNode * node, int search_value){
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

static int BinarySearchTree_init(BinarySearchTree *self, PyObject *args){
    self->root = NULL;

    PyObject* list = NULL;
    if( ! PyArg_ParseTuple(args, "O", &list)){
        return -1;
    }
    if( ! PyList_Check(list) ){
        return -1;
    }

    if( PyLong_Check(PyList_GetItem(list, 0)) ){
        int root_value = PyLong_AsLong( PyList_GetItem(list, 0) );
//        fprintf(stderr, "[0]: %d \n", root_value );
        self->root = node_new( root_value );
    }

    for( int i=1; i < PyList_Size(list); ++i ){
        int each_value = PyLong_AsLong( PyList_GetItem(list, i) );
        //fprintf(stderr, "[%d] = %d \n", i, each_value );
        node_add( self->root, each_value );
    }


    return 0;
}

static void BinarySearchTree_dealloc(BinarySearchTree *self){
    PyTypeObject *tp = Py_TYPE(self);

    // free references and buffers here
    node_free(self->root);

    tp->tp_free(self);
    Py_DECREF(tp);
}

static PyObject* tree_search( PyObject* self, PyObject* search_value){
    // ignore null check

    BinarySearchTree* tree = (BinarySearchTree*) self;
    if( ! PyLong_Check(search_value)){
        Py_RETURN_NONE;
    }

    int found_value = node_search( tree->root, PyLong_AsLong(search_value));
    if( 0 < found_value ){
        return Py_BuildValue("i", found_value);
    }

    Py_RETURN_NONE;
}

static PyMethodDef BinarySearchTree_methods[] = {
    { "search", tree_search, METH_O,           "search this tree for a particular value" },
    { NULL }
};

static PyTypeObject BinarySearchTreeType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "BinarySearchTree",                        /* tp_name */
    sizeof(BinarySearchTree),                  /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)BinarySearchTree_dealloc,      /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "BinarySearchTree object",                 /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    BinarySearchTree_methods,                  /* tp_methods */
    0,                         /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)BinarySearchTree_init,           /* tp_init */
    0,                         /* tp_alloc */
    PyType_GenericNew,                        /* tp_new */
};

// Module functions table
// static PyMethodDef BinarySearchTreeModule_StaticMethods[] = {
static PyMethodDef module_methods[] = {
//    { "new", tree_new, METH_O, "create a new tree" }, /// TODO: Implement me!
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef cModuleBinarySearchTree = {
    PyModuleDef_HEAD_INIT,
    "BinarySearchTree", /* name of module */
    " <doc-string> ",   /* module docstring */
    -1,                 /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    module_methods
};

// NEW: Python3 example:
PyMODINIT_FUNC PyInit_BinarySearchTree(void) {
    PyObject* mod = PyModule_Create(&cModuleBinarySearchTree);

   // Fill in some slots in the type, and make it ready
   if (PyType_Ready(&BinarySearchTreeType) < 0) {
      return mod;
   }

   // Add the type to the module.
   Py_INCREF(&BinarySearchTreeType);
   PyModule_AddObject(mod, "BinarySearchTree", (PyObject*)&BinarySearchTreeType);

    return mod;
}

