#include "fileB.h"

extern int x; // gives us access to variable x defined in fileA.c

void foo(){
	x += 7;
}
