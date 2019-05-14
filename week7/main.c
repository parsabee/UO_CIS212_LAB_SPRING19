#include "linkedlist.h"
#include <stdio.h>
#define UNUSED __attribute__((unused))

int main (UNUSED int argc, UNUSED char *argv[]) {
	const LinkedList *ll = LinkedList_create ();
	long arr [] = {1L, 2L, 3L, 4L};
	for (int i = 0; i < 4; i++)
		ll->addLast (ll, (void *)arr [i]);
	
	long tmp;
	ll->getLast (ll, (void **) &tmp);
	printf("last : %ld\n", tmp);
}