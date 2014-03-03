CFLAGS=-g -Wall
CC=gcc
all: strtest
strtest: main.o str.o
	$(CC) main.o str.o -o strtest
clean:
	rm -f main.o strtest
