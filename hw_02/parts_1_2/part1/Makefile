CCFLAGS = -ggdb -Wall -m32

all: my_timer.o part1.o part1

my_timer.o: my_timer.c my_timer.h
	gcc $(CCFLAGS) -c my_timer.c my_timer.h

part1.o: part1.c
	gcc $(CCFLAGS) -c part1.c

part1: my_timer.o part1.o
	gcc $(CCFLAGS) my_timer.o part1.o -o part1

clean:
	rm -rf part1 *.o *.dSYM *.gch
