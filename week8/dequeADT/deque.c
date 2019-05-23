/*
 * Author: Parsa Bagheri
 * deque.c
 *
 * A simple implementation of the `deque' data structure
 * using a doubly linked-list
 */

#include "deque.h"
#include <stdlib.h>

typedef struct node Node;
struct node {
	void *value;
	Node *next;
	Node *prev;
};

typedef struct data Data;
struct data {
	Node *head;
	Node *tail;
	long size;
};

static int d_push_b (const Deque *d, void *element) {
	Data *dd = (Data *)d->self;
	int status = 0;
	Node *new = (Node *)malloc (sizeof (Node));
	if (new) {
		status = 1;
		new->next = NULL;
		new->value = element;
		new->prev = dd->tail;
		dd->size++;
		if (dd->tail)
			dd->tail->next = new;	
		else 
			dd->head = new;
		dd->tail = new;
	}
	return status;
}

static int d_push_f (const Deque *d, void *element) {	
	Data *dd = (Data *)d->self;
	int status = 0;
	Node *new = (Node *)malloc (sizeof (Node));
	if (new) {
		status = 1;
		new->next = dd->head;
		new->value = element;
		new->prev = NULL;
		dd->size++;
		if (dd->head)
			dd->head->prev = new;
		else 
			dd->tail = new;
		dd->head = new;
	}
	return status;
}

static int d_pop_b (const Deque *d, void **element) {
	Data *dd = (Data *)d->self;
	if (!(dd->size))
		return 0;
	*element = dd->tail->value;
	Node *tmp = dd->tail->prev;
	if (tmp == NULL)
		dd->head = NULL;
	free (dd->tail);
	dd->tail = tmp;
	dd->size--;
	return 1;
}

static int d_pop_f (const Deque *d, void **element) {
	Data *dd = (Data *)d->self;
	if (!(dd->size))
		return 0;
	*element = dd->head->value;
	Node *tmp = dd->head->next;
	if (tmp == NULL)
		dd->tail = NULL;
	free (dd->head);
	dd->head = tmp;
	dd->size--;
	return 1;
}

static int d_front (const Deque *d, void **element) {
	Data *dd = (Data *)d->self;
	if (!(dd->size))
		return 0;
	*element = dd->head->value;
	return 1;	
}

static int d_back (const Deque *d, void **element) {
	Data *dd = (Data *)d->self;
	if (!(dd->size))
		return 0;
	*element = dd->tail->value;
	return 1;	
}

static long d_size (const Deque *d) {
	Data *dd = (Data *)d->self;
	return dd->size;
}

static void **d_toArray (const Deque *d, long *len) {
	Data *dd = (Data *)d->self;
	void **array = NULL;
	if (dd->size) {
		array = (void **)malloc (sizeof (void *) * dd->size);
		if (array) {
			long i = 0;
			for (Node *tmp = dd->head; tmp != NULL; tmp = tmp->next)
				array [i++] = tmp->value;
			*len = dd->size;
		}
	}
	return array;
}

static void purge (Data *dd, void (*freeFxn)(void *)) {
	Node *next = NULL;
	for (Node *tmp = dd->head; tmp != NULL; tmp = next) {
		if (freeFxn)
			freeFxn (tmp->value);
		next = tmp->next;
		free (tmp);
	}
}

static void d_clear (const Deque *d, void (*freeFxn)(void *)) {
	Data *dd = (Data *)d->self;
	purge (dd, freeFxn);
	dd->tail = dd->head = NULL;
	dd->size = 0L;
}

static void d_destroy (const Deque *d, void (*freeFxn)(void *)) {
	Data *dd = (Data *)d->self;
	purge (dd, freeFxn);
	free (dd);
	free ((void *)d);
}

static Deque template = {
	NULL, d_push_b, d_push_f, d_pop_b, d_pop_f,
	d_front, d_back, d_size,d_toArray ,d_clear, d_destroy
};

const Deque *Deque_create (void) {
	Deque *d = (Deque *) malloc (sizeof (Deque));
	if (d != NULL) {
		Data *dd = (Data *) malloc (sizeof (Data));
		if (dd != NULL) {
			dd->size = 0L;
			dd->head = dd->tail = NULL;
			*d = template;
			d->self = dd;
		}
		else {
			free (d);
			d = NULL;
		}
	}
	return d;
}	
