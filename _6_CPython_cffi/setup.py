from setuptools import setup

setup(
    setup_requires=["cffi>=1.0.0"],
    cffi_modules=["piapprox_build:ffibuilder"], # "filename:global"
    install_requires=["cffi>=1.0.0"],
)