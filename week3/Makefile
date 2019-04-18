CFLAGS = -Wall
CC = gcc
TARGETS = scat echo
RM = rm -f

all: $(TARGETS)

scat: scat.c
	$(CC) $(CFLAGS) -o scat $^

echo: echo.c
	$(CC) $(CFLAGS) -o echo $^

clean:
	$(RM) $(TARGETS)


