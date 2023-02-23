CC = gcc
CFLAGS = -g -Wall

all: memgrind

mymalloc: mymalloc.c
				$(CC) $(CFLAGS) -o mm mymalloc.c
				
memgrind: memgrind.c mymalloc.c mymalloc.h
				$(CC) $(CFLAGS) -c mymalloc.c
				$(CC) $(CFLAGS) -o memgrind memgrind.c mymalloc.o
clean:
			rm -f mymalloc.o memgrind
