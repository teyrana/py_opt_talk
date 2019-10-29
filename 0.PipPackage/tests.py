#!/usr/bin/env python3

import binarytree

import unittest


class TestBinaryTree(unittest.TestCase):

    def test_creation(self):
        # this creates a fully-populated binary-search-tree of depth 4, on the numbers [0, 30]
        root = binarytree.bst(height=4, is_perfect=True)

        # DEBUG
        # print(root)

        # ==== generates this tree: ====
        #                 ___________________15_____________________
        #                /                                          \
        #         ______7_______                           __________23_________
        #        /              \                         /                     \
        #     __3__           ___11___               ____19___               ____27___
        #    /     \         /        \             /         \             /         \
        #   1       5       9         _13         _17         _21         _25         _29
        #  / \     / \     / \       /   \       /   \       /   \       /   \       /   \
        # 0   2   4   6   8   10    12    14    16    18    20    22    24    26    28    30
        #
        self.assertEqual(root.height, 4)

        # spot check -- *not full* check:
        self.assertEqual(root.value, 15)
        self.assertEqual(root.right.value, 23)
        self.assertEqual(root.right.left.value, 19)
        self.assertEqual(root.right.left.left.value, 17)
        self.assertEqual(root.right.left.left.left.value, 16)
        self.assertEqual(root.right.left.left.right.value, 18)


    def test_search(self):
        root = binarytree.bst()




if __name__ == '__main__':
    unittest.main()
