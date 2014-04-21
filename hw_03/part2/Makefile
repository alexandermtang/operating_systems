CCFLAGS = -ggdb -Wall -m32 -pthread

all: mypthread.o part2.o part2 part2_posix

mypthread.o: mypthread.c mypthread.h
	gcc $(CCFLAGS) -c mypthread.c mypthread.h

part2.o: part2.c
	gcc $(CCFLAGS) -c part2.c

part2: mypthread.o part2.o
	gcc $(CCFLAGS) mypthread.o part2.o -o part2

part2_posix: part2_posix.c
	gcc $(CCFLAGS) part2_posix.c -o part2_posix

clean:
	rm -rf part2 part2_posix *.o *.dSYM *.gch
