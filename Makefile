CFLAGS=-g
CC=gcc
all: strtest
strtest: main.o str.o
clean:
	rm -f main.o strtest
