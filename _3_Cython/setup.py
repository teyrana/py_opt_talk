from distutils.core import setup
from Cython.Build import cythonize


ext_modules = cythonize(
    "bst/*.pyx")

setup(
    name='BinaryTree',
    ext_modules=ext_modules
)