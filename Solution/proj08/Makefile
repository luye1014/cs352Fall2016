#FLAGS=-Wall -g -fprofile-arcs -ftest-coverage
FLAGS=-Wall -O3



example_lineSort: main.o util.o
	gcc $(FLAGS) main.o util.o -o example_lineSort

main.o: main.c util.h
	gcc $(FLAGS) -c main.c -o main.o

util.o: util.c util.h
	gcc $(FLAGS) -c util.c -o util.o


clean:
	-rm main.o util.o example_lineSort *.gcno *.gcda *.c.gcov
