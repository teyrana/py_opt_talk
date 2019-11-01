
#cython: language_level=3
#distutils: language=c++

from libcpp.vector cimport vector

cdef class Node:
    cdef Node _left
    cdef Node _right
    cdef int _value

cdef Node new( vector[int] init)

cdef void add( Node node, int new_value)

cdef int search( Node node, int search_value)