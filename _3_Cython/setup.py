from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize
from Cython.Distutils import build_ext



ext_modules = cythonize([
    "src/node.pyx",
    "src/tree.pyx",
    # Extension("src",  ["src/node.py", "src/tree.py"]), compiler_directives={'language_level': "3"},
    # setup(ext_modules=cythonize(["landscaping.pyx", "shrubbing.pyx"]))
])

setup(
    name='BinaryTree',
    ext_modules=ext_modules
)