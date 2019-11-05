#include <stdlib.h>
#include <string.h>

#include "Python.h"

#include "node.h"

// Binary trees can also be stored in breadth-first order as an implicit data structure in arrays:
//   - If a node has an index i, its children are found at indices `2i+1` (for the left child) and `2i+2` (for the right)
//   - If a node has an index i, its parent (if any) is found at index `floor((i-1)/(2))`  (assuming the root has index zero). 
// This method benefits from more compact storage and better locality of reference, particularly during a preorder traversal. 
// However, it is expensive to grow and wastes space proportional to 2h - n for a tree of depth h with n nodes.
// 
// +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
// | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| 11| 12| 13| 14|
// +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
//   15
//        7  23
//                3  11  19  27
//                                1   5   9  13  17  21  25  29
//
// +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
// | 15|  7| 23|  3| 11| 19| 27|  1|  5|  9| 13| 17| 21| 25| 29|
// +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
//
// Index  -->  Index 
//    0 -> l -> 1
//    0 -> r -> 2
//    5 -> l -> 11
//    6 -> r -> 14
//


typedef struct _binary_search_tree {
    PyObject_HEAD;
    int * data;
    int allocated;
} BinarySearchTree;

const int SENTINEL_VALUE = 0;

void tree_add(BinarySearchTree* self, int new_value){
    // fprintf(stderr, "++ adding value: %2d\n", new_value);
    int search_index = 0;
    while(search_index < self->allocated){
        // fprintf(stderr, "    @[ %2d] = %2d\n", search_index, self->data[search_index] );
        if( SENTINEL_VALUE == self->data[search_index] ){
            self->data[search_index] = new_value;
            return;
        }else if(self->data[search_index] > new_value){
            // increment to left branch
            search_index = 2 * search_index + 1;
        }else{
            // increment to right branch
            search_index = 2 * search_index + 2;
        }
    }
}

void tree_dump(BinarySearchTree* self, FILE* dest ){
    fprintf(dest, "-- [");
    for( int i=0; i < self->allocated; ++i ){
        fprintf(dest, " %2d", i);
    }
    fprintf(dest, " ] -- \n");
    
    fprintf(dest, "## [");
    for( int i=0; i < self->allocated; ++i ){
        if( self->data[i] < 0 || 0xFF < self->data[i]){
            fprintf(dest, " --");
        }else{
            fprintf(dest, " %2d", self->data[i]);
        }
    }
    fprintf(dest, " ]\n");
}

void tree_reset(BinarySearchTree* self, int size){
    if(self->allocated >= size){
        return;
    }

    int next_size = 4;
    while( next_size < size){
        next_size <<= 1;
    }

    int* new_buffer = malloc(sizeof(int)*next_size);
    memset(new_buffer, SENTINEL_VALUE, sizeof(int)*next_size);
    if( NULL != self->data){
        memcpy(new_buffer, self->data, self->allocated);
        free(self->data);
    }
    
    self->data = new_buffer;
    self->allocated = next_size;

    return;
}

static int BinarySearchTree_init(BinarySearchTree *self, PyObject *args){
    self->data = NULL;
    self->allocated = 0;

    PyObject* list = NULL;
    if( ! PyArg_ParseTuple(args, "O", &list)){
        return -1;
    }
    if( ! PyList_Check(list) ){
        return -1;
    }

    int new_size = PyList_Size(list);
    if( 0 < new_size ){
        tree_reset(self, new_size);
    }

    for( int i=0; i < PyList_Size(list); ++i ){
        int each_value = PyLong_AsLong( PyList_GetItem(list, i) );
        tree_add( self, each_value );
    }

    return 0;
}

static void BinarySearchTree_dealloc(BinarySearchTree *self){
    PyTypeObject *tp = Py_TYPE(self);

    self->allocated = 0;
    free(self->data);

    tp->tp_free(self);
    Py_DECREF(tp);
}

static PyObject* tree_search( PyObject* self, PyObject* search_object){
    if( ! PyLong_Check(search_object)){
        Py_RETURN_NONE;
    }
    int search_value = PyLong_AsLong(search_object);

    BinarySearchTree* tree = (BinarySearchTree*)self;
    int search_index = 0;
    while(search_index < tree->allocated){
        if( search_value == tree->data[search_index] ){
            tree->data[search_index] = search_value;
            return Py_BuildValue("i", tree->data[search_index]);
        }else if(tree->data[search_index] > search_value){
            // increment to left branch
            search_index = 2 * search_index + 1;
        }else{
            // increment to right branch
            search_index = 2 * search_index + 2;
        }
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

