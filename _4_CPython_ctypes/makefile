

all: run

build:
	mkdir -p build

clean:
	rm -f *.o *.so *.html


lib: build/libbst.so

build/libbst.so: bst/tree.c
	gcc -shared -Wall -Werror -fpic bst/tree.c -o build/libbst.so

# option 2: 
#  -framework Python

# point: export LD_LIBRARY_PATH = $(shell pwd)

