#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#define UNUSED __attribute__((unused))
#define print(remove, add)\
	while ((*ll)->remove(*ll, (void **)&element)){\
		printf("%ld ", element);\
		tmp->add(tmp, (void *)element);\
	}\
	
void printll (const LinkedList **ll, int backwards) {
	if (!(*ll)->size(*ll))
		return;
	const LinkedList *tmp = LinkedList_create ();
	long element;
	if (backwards)
		print (removeLast, addFirst)
	else
		print (removeFirst, addLast)
	printf("\n");
	(*ll)->destroy(*ll, NULL);
	*ll = tmp;
}

int main (UNUSED int argc, UNUSED char *argv[]) {
	const LinkedList *ll = LinkedList_create ();
	if (ll == NULL)
		return 0;
	
	long arr [] = {1L, 2L, 3L, 4L};
	for (int i = 0; i < 4; i++)
		ll->addLast (ll, (void *)arr [i]);
	
	fprintf (stderr, "printing LinkedList:\n");	
	printll (&ll, 0);
	fprintf (stderr, "printing LinkedList backwards:\n");	
	printll (&ll, 1);
	fprintf (stderr, "calling toArray method on LinkedList:\n");	
	long len;
	void **array = ll->toArray (ll, &len);
	if (array != NULL) {
		for (long i = 0; i < len; i++)
			printf ("%ld ", (long)array[i]);
		printf ("\n");
		free (array);
	}
	ll->clear (ll, NULL);
	fprintf (stderr, "printing after clearing LinkedList:\n");	
	printll(&ll, 0);
	ll->destroy (ll, NULL);

	return 1;
}
