CFLAGS=-W -Wall
OBJECTS=stringADTexample.o stringADT.o arraylist.o iterator.o

stringADTexample: $(OBJECTS)
	gcc -g -o stringADTexample $(OBJECTS)

stringADTexample.o: stringADTexample.c stringADT.h arraylist.h
stringADT.o: stringADT.c stringADT.h arraylist.h
arraylist.o: arraylist.c arraylist.h iterator.h
iterator.o: iterator.c iterator.h

clean:
	rm -f stringADTexample $(OBJECTS)
