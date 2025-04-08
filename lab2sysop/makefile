CC = gcc
CFLAGS = -Wall -std=c17

.PHONY: shared static client1 client2 client3 clean

shared: libshared.so

libshared.so: collatz.o
	$(CC) $(CFLAGS) -shared collatz.o -o libshared.so

static: staticlib.a

staticlib.a: collatz.o
	ar rcs staticlib.a collatz.o

collatz.o: collatz.c
	$(CC) $(CFLAGS) -fPIC -c collatz.c -o collatz.o

client1: staticlib.a client.c
	$(CC) $(CFLAGS) client.c staticlib.a -o client1

client2: libshared.so client.c
	$(CC) $(CFLAGS) client.c -L. -lshared -Wl,-rpath,. -o client2

client3: client.c
	$(CC) $(CFLAGS) -DDYNAMIC client.c -o client3 -ldl

clean:
	rm -f client1 client2 client3 collatz.o libshared.so staticlib.a
