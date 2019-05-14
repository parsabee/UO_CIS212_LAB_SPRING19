SOURCES = $(wildcard *.c)
OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))
CFLAGS = -W -Wall -g
CC = gcc
TARGETS = main
RM = rm -rf

all: $(TARGETS)

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(TARGETS) $(OBJECTS)
