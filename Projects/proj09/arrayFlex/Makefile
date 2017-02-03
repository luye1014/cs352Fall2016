CFLAGS = -g -fprofile-arcs -ftest-coverage -Wall
tanme = test_arrayFlex
tstSrc = $(wildcard test_arrayFlex_*.c)
tstExe = $(tstSrc:.c=)

.PHONY: all, clean

all: $(tstExe)

$(tstExe):%: %.o arrFlex.o
	gcc $(CFLAGS) -o $@ $*.o arrFlex.o

%.o: %.c arrFlex.h
	gcc $(CFLAGS) -c $<

clean:
	/bin/rm -f arrFlex *.gcda *.gcno test_arrayFlex_*.o arrFlex.o *.gcov my.out