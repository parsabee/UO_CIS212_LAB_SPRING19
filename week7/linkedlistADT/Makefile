SOURCES = $(wildcard *.c)
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))
CFLAGS = -W -Wall -g
CC = gcc
TARGETS = test
RM = rm -rf

all: $(TARGETS)

test: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(TARGETS) $(OBJECTS)
