/*
 * author: Parsa Bagheri
 * linkelist.c
 * a simple doubly linked list implementation
 */

#include "linkedlist.h"
#include <stdlib.h>

typedef struct linkedlist_node Node;
struct linkedlist_node {
	void *data;
	Node *next;
	Node *prev;
};

typedef struct linkedlist_data {
	Node *head;
	Node *tail;
	int size;
} Data;

static int _addLast (const LinkedList *ll, void *element) {
	Data *_data = (Data *)ll->self;
	Node *node = (Node *)malloc (sizeof (Node));
	if (node != NULL) {
		node -> data = element;
		node -> prev = _data -> tail;
		node -> next = NULL;
		_data -> tail = node;
		_data -> size ++;
		return 1;
	}
	return 0;
}

static int _addFirst (const LinkedList *ll, void *element) {
	Data *_data = (Data *)ll->self;
	Node *node = (Node *)malloc (sizeof (Node));
	if (node != NULL) {
		node -> data = element;
		node -> prev = NULL;
		node -> next = _data->head;
		_data -> head = node;
		_data -> size ++;
		return 1;
	}
	return 0;
}

static int _getLast (const LinkedList *ll, void **element) {
	Data *_data = (Data *)ll->self;
	Node *tmp = _data->tail;
	if (tmp != NULL) {
		*element = tmp->data;
		return 1;
	}
	return 0;
}

static int _getFirst (const LinkedList *ll, void **element) {
	Data *_data = (Data *)ll->self;
	Node *tmp = _data->head;
	if (tmp != NULL) {
		*element = tmp->data;
		return 1;
	}
	return 0;
}

static void _destroy (const LinkedList *ll, void(*freeFxn)(void *element)) {
	Data *_data = (Data *)ll->self;
	Node *curnode = _data->head;
	while (curnode != NULL) {
		Node *tmp = curnode->next;
		if (freeFxn != NULL)
			freeFxn (curnode->data);
		free (curnode);
		curnode = tmp;
	}
}

static int _size (const LinkedList *ll) {
	Data *_data = (Data *)ll->self;
	return _data->size;
}

const LinkedList *LinkedList_create () {
	Data *_data = (Data *)malloc (sizeof (Data));
	if (_data != NULL) {
		_data->head = NULL;
		_data->tail = NULL;
		_data->size = 0;

		LinkedList *_linkedlist = (LinkedList *)malloc (sizeof (LinkedList));
		if (_linkedlist != NULL) {
			_linkedlist->self = (void *)_data;
			_linkedlist->addLast = _addLast;
			_linkedlist->addFirst = _addFirst;
			_linkedlist->destroy = _destroy;
			_linkedlist->getFirst = _getFirst;
			_linkedlist->getLast = _getLast;
			_linkedlist->size = _size;
		} else 
			free (_data);

		return _linkedlist;
	}
	
	return NULL;
}