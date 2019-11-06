// declarations that are shared between Python and C

struct BinarySearchNode {
    struct BinarySearchNode * left;
    struct BinarySearchNode * right;
    int value;
};

struct BinarySearchNode* node_new( int init_value);
void node_add( struct BinarySearchNode * node, int new_value);
void node_free( struct BinarySearchNode* node);
int node_search( struct BinarySearchNode * node, int search_value);