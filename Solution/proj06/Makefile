all: example_tokenize

example_tokenize:      example_tokenize.c
	gcc -Wall -O3 example_tokenize.c -o example_tokenize
#	gcc -Wall -g -fprofile-arcs -ftest-coverage example_tokenize.c -o example_tokenize



clean:
	-rm example_tokenize example_tokenize.gcno example_tokenize.gcda example_tokenize.c.gcov
