CC=gcc
CFLAGS=-I.
DEPS = vector.h

all: svp.o vector.o
	$(CC) -o svp svp.o vector.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o svp vector