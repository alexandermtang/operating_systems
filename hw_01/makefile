CC=gcc
CFLAGS=-Wall -g

build:
	make my_timer.o part1a.o part1b.o part1c.o part2.o part3.o
	make part1a part1b part1c part2 part3

clean:
	-rm -rf *.o part1a part1b part1c part2 part3 *.dSYM

rebuild:
	make clean build

# Tools =======================================================================
my_timer.o: my_timer.h my_timer.c
	$(CC) $(CFLAGS) -c my_timer.c

# Part 1 ======================================================================
part1a: my_timer.o part1a.o
	$(CC) $(CFLAGS) my_timer.o part1a.o -o part1a -lm
part1a.o: part1a.c
	$(CC) $(CFLAGS) -c part1a.c

part1b: my_timer.o part1b.o
	$(CC) $(CFLAGS) my_timer.o part1b.o -o part1b -lm
part1b.o: part1b.c
	$(CC) $(CFLAGS) -c part1b.c

part1c: my_timer.o part1c.o
	$(CC) $(CFLAGS) my_timer.o part1c.o -o part1c -lm
part1c.o: part1c.c
	$(CC) $(CFLAGS) -c part1c.c

# Part 2 ======================================================================
part2: my_timer.o part2.o
	$(CC) $(CFLAGS) my_timer.o part2.o -o part2

part2.o: part2.c
	$(CC) $(CFLAGS) -c part2.c

# Part 3 ======================================================================
part3: my_timer.o part3.o
	$(CC) $(CFLAGS) my_timer.o part3.o -o part3

part3.o: part3.c
	$(CC) $(CFLAGS) -c part3.c
