CFLAGS = -O2 -Wall -Wextra -std=c2x -Wconversion

.PHONY: all clean

all: osvm

osvm: osvm.o osutils.o
	cc $(CFLAGS) $^ -o $@

osvm.o: osvm.c osvm.h
	cc $(CFLAGS) -c $< -o $@

osutils.o: osutils.c osutils.h
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o osvm

