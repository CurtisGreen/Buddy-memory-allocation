# makefile

all: memtest


my_allocator.o : my_allocator.c
	g++ -c -g my_allocator.c

memtest.o : memtest.c
	g++ -c -g memtest.c

memtest: memtest.o my_allocator.o
	g++ -o memtest memtest.o  my_allocator.o

