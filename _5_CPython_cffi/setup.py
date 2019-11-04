#!/usr/bin/env python3

from distutils.core import setup, Extension

setup(
    name="BinarySearchTree",
    ext_modules=[
        Extension("BinarySearchTree", sources=["bst/tree.c"]),
    ]
)
