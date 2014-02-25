CFLAGS=-g
CC=gcc
all: strtest 
strtest: main
clean:
	rm -f main.o strtest
