CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

all: flipper

flipper: flipper.o
	$(CC) $(CFLAGS) -o flipper flipper.o

flipper.o: flipper.c
	$(CC) $(CFLAGS) -c flipper.c

clean:
	rm -f flipper.o flipper

.PHONY: all clean
