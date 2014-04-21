CCFLAGS = -ggdb -Wall -m32 -pthread

all: mypthread.o part2.o part2

mypthread.o: mypthread.c mypthread.h
	gcc $(CCFLAGS) -c mypthread.c mypthread.h

part2.o: part2.c
	gcc $(CCFLAGS) -c part2.c

part2: mypthread.o part2.o
	gcc $(CCFLAGS) mypthread.o part2.o -o part2

clean:
	rm -rf part2 *.o *.dSYM *.gch
