# FLAGS = -g -fprofile-arcs -ftest-coverage -Wall
# thames = test_arrayFlex_
# tstSrc = $(wildcard test_arrayFlex_*.c)
# tstExe = $(tstSrc:.c=)

# .PHONY: all
# all: $(tstExe)

# $(tstExe):%: %.o example_arrFlex.o
# 	gcc $(FLAGS) -o $@ $*.o example_arrFlex.o

# %.o: %.c arrFlex.h
# 	gcc $(FLAGS) -c $<
arrFlex:arrFlex.o test_arrayFlex_01_eachCall.o
	gcc -fprofile-arcs -ftest-coverage -g arrFlex.o test_arrayFlex_01_eachCall.o -o arrFlex
arrFlex.o:arrFlex.c arrFlex.h
	gcc -Wall -fprofile-arcs -ftest-coverage -g -c arrFlex.c
test_arrayFlex_01_eachCall.o:test_arrayFlex_01_eachCall.c arrFlex.h
	gcc -Wall -fprofile-arcs -ftest-coverage -g -c test_arrayFlex_01_eachCall.c