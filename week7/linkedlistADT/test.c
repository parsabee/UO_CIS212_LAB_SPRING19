#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#define UNUSED __attribute__((unused))
#define print(backwards)\
	if (backwards){\
		while ((*ll)->removeLast(*ll, (void **)&element)){\
			printf("%ld ", element);\
			tmp->addFirst(tmp, (void *)element);\
		}\
	}\
	else{\
		while ((*ll)->removeFirst(*ll, (void **)&element)){\
			printf("%ld ", element);\
			tmp->addLast(tmp, (void *)element);\
		}\
	}\
	printf("\n");\

void printll (const LinkedList **ll, int backwards) {
	const LinkedList *tmp = LinkedList_create ();
	long element;
	print(backwards);
	(*ll)->destroy(*ll, NULL);
	*ll = tmp;
}

int main (UNUSED int argc, UNUSED char *argv[]) {
	const LinkedList *ll = LinkedList_create ();
	long arr [] = {1L, 2L, 3L, 4L};
	for (int i = 0; i < 4; i++)
		ll->addLast (ll, (void *)arr [i]);
	
	fprintf (stderr, "printing LinkedList:\n\t");	
	printll (&ll, 1);
	fprintf (stderr, "printing LinkedList backwards:\n\t");	
	printll (&ll, 0);
	fprintf (stderr, "calling toArray method on LinkedList:\n\t");	
	long len;
	void **array = ll->toArray (ll, &len);
	for (long i = 0; i < len; i++)
		printf ("%ld ", (long)array[i]);
	printf ("\n");
	free (array);
	ll->clear (ll, NULL);
	fprintf (stderr, "printing after clearing LinkedList:\n\t");	
	printll(&ll, 0);
	ll->destroy (ll, NULL);
}
