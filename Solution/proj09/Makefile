CC=gcc

CFLAGS=-Wall -O3
#CFLAGS=-Wall -g -fprofile-arcs -ftest-coverage

TESTCASE_SRCS=$(wildcard test_arrayFlex_*.c)
TESTCASES=$(TESTCASE_SRCS:.c=)



all: $(TESTCASES)

$(TESTCASES): example_arrFlex.o

#example_arrFlex.o: example_arrFlex.c arrFlex.h
#	gcc -Wall -O3 -c example_arrFlex.c -o example_arrFlex.o


clean:
	-rm *.o $(TESTCASES) *.gcno *.gcda *.c.gcov
