#!/usr/bin/env python3

import unittest

import _bst.lib as bst

class TestBinaryTree(unittest.TestCase):

    def new_tree(self, init_values):
        root = bst.node_new(init_values[0])
        for value in init_values:
            bst.node_add(root, value)
        return root

    def test_create_from_list(self):
        """This method creates a fully-populated binary-search-tree of depth 4, on the numbers: [0, 30]"""

        #
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

        root = bst.node_new(15)
        bst.node_add(root, 7)
        bst.node_add(root, 23)

        # ^^^ success

        # vvv failure

        # If we add the above values in the correct order, the tree is balanced, for free.
        tree = self.new_tree([15,
                                7, 23,
                                3, 11, 19, 27,
                                1, 5, 9, 13, 17, 21, 25, 29,
                                0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30])
        # DEBUG
        # print(str(root))

        # again spot checks -- verify that the tree can find values it contains
        self.assertEqual(bst.node_search(tree, 8), 8)
        self.assertEqual(bst.node_search(tree, 16), 16)
        self.assertEqual(bst.node_search(tree, 17), 17)
        self.assertEqual(bst.node_search(tree, 18), 18)
        self.assertEqual(bst.node_search(tree, 19), 19)
        self.assertEqual(bst.node_search(tree, 24), 24)

        # # spot check -- *not full* check:
        # self.assertEqual(node.value(tree), 15)
        # self.assertEqual(node.value(node.right(tree)), 23)
        # self.assertEqual(node.value(node.left(node.right(tree))), 19)
        # self.assertEqual(node.value(node.left(node.left(node.right(tree)))), 17)
        # self.assertEqual(node.value(node.left(node.left(node.left(node.right(tree))))), 16)
        # self.assertEqual(node.value(node.right(node.left(node.left(node.right(tree))))), 18)


if __name__ == '__main__':
    unittest.main()
