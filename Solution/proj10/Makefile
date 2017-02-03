flags = -g -Wall
OBJS = makeThis.o graphTools.o

makeThis : $(OBJS)
	gcc $(flags) $(OBJS) -o makeThis

%.o : %.c
	gcc $(flags) -c $<

.PHONY : clean
clean : 
	rm -f *.o makeThis