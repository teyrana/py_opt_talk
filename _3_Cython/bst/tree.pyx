

#cython: language_level=3
#distutils: language=c++

from libcpp.vector cimport vector

cdef class Node:
    def __init__(self, _value):
        self._left = None
        self._right = None
        self._value = _value

    @property
    def left(self):
        return self._left

    @property
    def right(self):
        return self._right

    @property
    def value(self):
        return self._value

cpdef Node new( vector[int] init):
    # ignore null check; ignore bounds check
    root = Node(init[0])
    for i in init:
        add(root, i)
    return root


cpdef void add( Node node, int new_value):
    # ignore null-case-check
    if new_value != node._value:
        if new_value < node._value:
            if None is node._left:
                node._left = Node(new_value)
            else:
                add(node._left, new_value)
        else:
            if None is node._right:
                node._right = Node(new_value)
            else:
                add(node._right, new_value)


cpdef int search( Node node, int search_value):
    # ignore null check
    if None is node:
        return -1
    elif search_value == node._value:
        return node._value
    elif (search_value < node._value) and (None is not node._left):
        return search(node._left, search_value)
    elif (search_value > node._value) and (None is not node._right):
        return search(node._right, search_value)
    else:
        return -1


