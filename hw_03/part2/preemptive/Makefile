CCFLAGS = -ggdb -Wall -m32 -pthread

all: mypthread.o mypthread_test.o mypthread_test

mypthread.o: mypthread.c mypthread.h
	gcc $(CCFLAGS) -c mypthread.c mypthread.h

mypthread_test.o: mypthread_test.c
	gcc $(CCFLAGS) -c mypthread_test.c

mypthread_test: mypthread.o mypthread_test.o
	gcc $(CCFLAGS) mypthread.o mypthread_test.o -o mypthread_test

clean:
	rm -rf mypthread_test *.o *.dSYM *.gch
