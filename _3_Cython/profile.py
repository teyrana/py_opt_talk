#!/usr/bin/env python3

import time
import random

import bst

def create_tree():
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

    # If we add the above values in the correct order, the tree is balanced, for free.
    root = bst.new([15,
                    7, 23,
                    3, 11, 19, 27,
                    1, 5, 9, 13, 17, 21, 25, 29,
                    0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30])
    return root


def run_time_trial(root, maxvalue, ncount = 100):

    start = time.process_time()

    # do the thing
    for _ in range(ncount):
        search_value = random.random() * maxvalue
        _ = bst.search(root, search_value)

    end = time.process_time()

    trial_time = end - start

    print(f"# Ran {ncount} trials over {trial_time} seconds.\n")


if __name__ == '__main__':

    root = create_tree()

    # dump_tree(root)

    run_time_trial(root, 30, ncount=1000000)
