all: bst352 example_bst352

bst352: bst352.c
	gcc -Wall -std=gnu99 -g -fprofile-arcs -ftest-coverage bst352.c -o bst352

example_bst352: bst352.c
	gcc -Wall -std=gnu99 -O3 bst352.c -o example_bst352

