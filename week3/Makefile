CFLAGS = -W -Wall
CC = gcc
TARGETS = scat echo
OBJECTS = scat.o echo.o
RM = rm -f

all: $(TARGETS)

scat: scat.o
	$(CC) -o scat $^

echo: echo.o
	$(CC) -o echo $^

scat.o: scat.c
echo.o: echo.c

clean:
	$(RM) $(TARGETS) $(OBJECTS)