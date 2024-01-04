CC=gcc
CFLAGS=-I. -O3
DEPS = vector.h

all: svp.o vector.o
	$(CC) -o runme svp.o vector.o -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o runme vector
	
test:
