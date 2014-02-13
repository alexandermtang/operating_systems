CC=gcc
CFLAGS=-Wall -g

build:
	make my_timer.o part1.o part2.o part1 part2

my_timer.o: my_timer.h my_timer.c
	$(CC) $(CFLAGS) -c my_timer.c

part1: my_timer.o part1.o
	$(CC) $(CFLAGS) my_timer.o part1.o -o part1 -lm

part1.o: part1.c
	$(CC) $(CFLAGS) -c part1.c

part2: my_timer.o part2.o
	$(CC) $(CFLAGS) my_timer.o part2.o -o part2

part2.o: part2.c
	$(CC) $(CFLAGS) -c part2.c

clean:
	-rm -rf *.o part1 part2 part3 *.dSYM

rebuild:
	make clean build
