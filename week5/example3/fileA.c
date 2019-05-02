/*
   x is defined here in fileA.c and declared as extern in fileB.c. This gives fileB.c access to x when the files are compiled and linked together. 
   To compile and link fileA.c, fileB.h, fileB.c, do the following. Run a.out to see the output:
   	gcc -c fileB.h fileB.c   
	gcc -c fileA.c
	gcc fileA.o fileB.o
*/

#include <stdio.h>
#include "fileB.h"

int x = 0;

int main(){
	printf("x initially has a value of %d\n", x); // x is initially 0
	
	foo(); // foo is defined in fileB.c
	
	printf("x now has a value of %d\n", x); // foo adds 7 to x. x is now 7

	return 0;
}
