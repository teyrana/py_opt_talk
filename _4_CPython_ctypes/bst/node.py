from ctypes import *

bst = cdll.LoadLibrary("build/libbst.so")


class BinaryTreeNode:
    pass

# class BinaryTreeNode(Structure):
#     _fields_ = [("left", c_void_p),
#                 ("right", c_void_p),
#                 ("value", c_int)]

    # def __str__(self, indent: int = 0) -> str:
    #     buf = ""
    #     next_indent = indent + 4
    #
    #     if None is not self.right:
    #         buf += self.right.__str__(next_indent)
    #
    #     buf += f"{''.rjust(indent)}- {self.value}\n"
    #
    #     if None is not self.left:
    #         buf += self.left.__str__(next_indent)
    #
    #     return buf


BinaryTreeNode.new = bst.node_new
BinaryTreeNode.new.argtypes = [c_int]
BinaryTreeNode.new.restype = c_void_p

BinaryTreeNode.get = bst.node_get_value
BinaryTreeNode.get.argtypes = [c_void_p]
BinaryTreeNode.get.restype = c_int

BinaryTreeNode.left = bst.node_get_left
BinaryTreeNode.left.argtypes = [c_void_p]
BinaryTreeNode.left.restype = c_void_p

BinaryTreeNode.right = bst.node_get_right
BinaryTreeNode.right.argtypes = [c_void_p]
BinaryTreeNode.right.restype = c_void_p

BinaryTreeNode.value = bst.node_get_value
BinaryTreeNode.value.argtypes = [c_void_p]
BinaryTreeNode.value.restype = c_int