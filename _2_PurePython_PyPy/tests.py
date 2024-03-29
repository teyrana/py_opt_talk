#!/Volumes/Branches/home/widget/project/talks/py_opt/_2_PurePython_PyPy/pypy-c-jit-97922-86da6cb357f1-osx64/bin/pypy

import unittest

from src import BinarySearchTree

class TestBinaryTree(unittest.TestCase):


    def test_create_from_list(self):
        # ==== which is equivalent to:
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
        # this creates a fully-populated binary-search-tree of depth 4, on the numbers: [0, 30]

        # if we add the above values in the correct order, the tree is balanced, for free.
        bst = BinarySearchTree([         15,
                            7,                           23,
                     3,          11,             19,             27,
                  1,    5,    9,     13,     17,     21,     25,     29,
                0,  2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30])

        # # DEBUG
        # print("===")
        # print(bst)
        # print("===")

        # spot check -- *not full* check:
        self.assertEqual(bst.root.value, 15)
        self.assertEqual(bst.root.right.value, 23)
        self.assertEqual(bst.root.right.left.value, 19)
        self.assertEqual(bst.root.right.left.left.value, 17)
        self.assertEqual(bst.root.right.left.left.left.value, 16)
        self.assertEqual(bst.root.right.left.left.right.value, 18)

        # again spot checks -- verify that the tree can find values it contains
        self.assertEqual(bst.search(8), 8)
        self.assertEqual(bst.search(16), 16)
        self.assertEqual(bst.search(18), 18)
        self.assertEqual(bst.search(24), 24)


if __name__ == '__main__':
    unittest.main()
