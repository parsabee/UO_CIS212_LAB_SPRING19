CFLAGS = -Wall -g -I./include
CC = gcc
LDFLAGS = -L./lib
LIBRARIES = -lADTs
TARGETS = wordperline
OBJECTS = wordperline.o
RM = rm -rf

all: $(TARGETS)

wordperline: wordperline.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o wordperline $^ $(LIBRARIES)

wordperline.o: wordperline.c

clean:
	$(RM) $(OBJECTS) $(TARGETS)
