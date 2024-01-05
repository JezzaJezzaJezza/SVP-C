CC=gcc
CFLAGS=-I. -O3
DEPS = vector.h

all: svp.o vector.o
	$(CC) -o runme svp.o vector.o -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o runme vector testProgram

test: all ./tests.c vector.o
	@echo "Starting tests"
	$(CC) -o testProgram ./tests.c vector.o -lm
	./testProgram
	@echo "Testing has finished... Cleaning"
	rm -f *.o runme vector testProgram