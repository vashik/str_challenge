CFLAGS=-g -Wall
CC=gcc
all: strtest
strtest: main.o str.o
	$(CC) main.o str.o -o strtest
str.o: str.c str.h

clean:
	rm -f main.o str.o strtest
