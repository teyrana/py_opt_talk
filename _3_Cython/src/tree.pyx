
#cython: language_level=3

from .node import BinaryTreeNode

class BinarySearchTree:
    def __init__(self, source = None):
        self.root = None
        if isinstance(source, dict):
            self.root = BinaryTreeNode(source)
        if isinstance(source, list):
            for i in source:
                self.add(i)

    def clear(self):
        # garbage collector will do this for us.
        self.root = None

    def add(self, value):
        if None is self.root:
            self.root = BinaryTreeNode(value)
        else:
            self.root.add(value)
        pass

    def search(self, value):
        if None is self.root:
            return None
        else:
            return self.root.search(value)

    def __str__(self):
        if None is not self.root:
            return str(self.root)
