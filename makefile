CC=gcc
CFLAGS=-I. -O3 -pg
DEPS = vector.h

all: svp.o vector.o
	$(CC) -o runme svp.o vector.o -pg

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o runme vector

test:
	