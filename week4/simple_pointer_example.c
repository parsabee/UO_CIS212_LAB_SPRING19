#include <stdio.h>

/*This example program illustrates basic pointer functionality.*/

int main(){
	int x = 6;

	int *y = &x; //make y point to x's value

	printf("memory address of x = %p\n", y);

	printf("value that y points to: %d", *y);

	x++;

	printf("\n\naddress of x = %p\n", y);

	printf("value that y points to: %d\n", *y);
	
	return 0;
}
