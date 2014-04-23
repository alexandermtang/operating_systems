CCFLAGS = -ggdb -Wall -m32 -pthread

all: mypthread.o test.o test

mypthread.o: mypthread.c mypthread.h
	gcc $(CCFLAGS) -c mypthread.c mypthread.h

test.o: test.c
	gcc $(CCFLAGS) -c test.c

test: mypthread.o test.o
	gcc $(CCFLAGS) mypthread.o test.o -o test

clean:
	rm -rf mypthread_test test *.o *.dSYM *.gch
