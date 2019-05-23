CFLAGS=-W -Wall -g
CC=gcc
OBJECTS=deque.o test.o print.o
TARGETS=test print

all: $(TARGETS)

test: deque.o test.o
	$(CC) $(CFLAGS) -o test $^

print: deque.o print.o
	$(CC) $(CFLAGS) -o print $^

deque.o: deque.c
test.o: test.c
print.o: print.c

clean:
	rm -rf $(OBJECTS) $(TARGETS)
