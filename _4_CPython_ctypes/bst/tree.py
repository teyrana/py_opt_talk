from ctypes import *

from .node import BinaryTreeNode

bst = cdll.LoadLibrary("build/libbst.so")


class BinarySearchTree:

    def __init__(self, init_values):
        self._root = BinaryTreeNode.new(init_values[0])
        for value in init_values:
            self.add(self.root, value)
        self._as_parameter_ = self._root

    @property
    def root(self):
        return self._root

    def add(self, value):
        pass

    def search(self, value):
        return -1

    def __str__(self) -> str:
        return ""


BinarySearchTree.add = bst.tree_add
BinarySearchTree.add.argtypes = [c_void_p, c_int]
BinarySearchTree.add.restype = None

BinarySearchTree.search = bst.tree_search
BinarySearchTree.search.argtypes = [c_void_p, c_int]
BinarySearchTree.search.restype = c_int
