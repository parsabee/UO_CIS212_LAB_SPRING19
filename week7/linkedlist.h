/*
 * author: Parsa Bagheri
 * linkelist.h
 * a simple doubly linked list implementation
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct linkedlist LinkedList;

const LinkedList *LinkedList_create (void); /* LinkedList *if successful, NULL otherwise */

struct linkedlist {
		void *self; /* private data */

		/* standard linked list methods, return 1 if successful, 0 otherwise */
		int (*addLast) (const LinkedList *ll, void *element);
		int (*addFirst) (const LinkedList *ll, void *element);
		int (*getLast) (const LinkedList *ll, void **element);
		int (*getFirst) (const LinkedList *ll, void **element);
		int (*size) (const LinkedList *ll);
		void (*destroy) (const LinkedList *ll, void(*freeFxn)(void *element));
};

#endif /* LINKEDLIST_H */