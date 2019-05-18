/*
 * author: Parsa Bagheri
 * linkelist.c
 * a simple singly linked list implementation
 */

#include "linkedlist.h"
#include <stdlib.h>

typedef struct linkedlist_node Node;
struct linkedlist_node {
	void *data;
	Node *next;
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
		node->data = element;
		node->next = NULL;
		if (_data->size == 0)
			_data->head = _data->tail = node;
		else {
			_data->tail->next = node;
			_data->tail = node;	
		}
		_data->size++;
		return 1;
	}
	return 0;
}

static int _addFirst (const LinkedList *ll, void *element) {
	Data *_data = (Data *)ll->self;
	Node *node = (Node *)malloc (sizeof (Node));
	if (node != NULL) {
		node->data = element;
		if (_data->size == 0){
			_data->head = _data->tail = node;
			node->next = NULL;
		}
		else{ 
			node->next = _data->head;
			_data->head = node;
		}
		_data->size++;
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

static int _removeLast (const LinkedList *ll, void **element) {
	Data *_data = (Data *)ll->self;
	if (!_data->size){
		*element = NULL;
		return 0;
	}

	Node *tmp, *prev = NULL; 
	for (tmp = _data->head; tmp->next != NULL; tmp = tmp->next)
		prev = tmp;

	*element = tmp->data;
	if (prev != NULL){
		prev->next = tmp->next;
		_data->tail = prev;
	}
	else 
		_data->head = _data->tail = NULL;
	
	_data->size--;
	free(tmp);
	return 1;
}

static int _removeFirst (const LinkedList *ll, void **element) {
	Data *_data = (Data *)ll->self;
	if (!_data->size){
		*element = NULL;
		return 0;
	}

	Node *tmp = _data->head->next;
       	*element = _data->head->data;
	free (_data->head);
	if (tmp == NULL)
		_data->head = _data->tail = NULL;
	else 
		_data->head = tmp;	
	_data->size--;
	return 1;
}

static void **_toArray (const LinkedList *ll, long *len) {
	Data *_data = (Data *)ll->self;
	*len = 0;
	if (!_data->size) 
		return NULL;
	
	void **array = (void **)malloc (sizeof(void *) *(_data->size));
	if (array) {
		*len = _data->size;
		long i = 0;
		for (Node *tmp = _data->head; tmp != NULL; tmp = tmp->next)
			array[i++] = tmp->data;
	}
	return array;
}

static void purge (Data *_data, void (*freeFxn)(void *element)) {
	Node *curnode = _data->head;
	while (curnode != NULL) {
		Node *tmp = curnode->next;
		if (freeFxn != NULL)
			freeFxn (curnode->data);
		free (curnode);
		curnode = tmp;
	}
}

static void _clear (const LinkedList *ll, void(*freeFxn)(void *element)) {
	Data *_data = (Data *)ll->self;
	purge (_data, freeFxn);
	_data->size = 0;
	_data->head = _data->tail = NULL;
}

static void _destroy (const LinkedList *ll, void(*freeFxn)(void *element)) {
	Data *_data = (Data *)ll->self;
	purge (_data, freeFxn);
	free (_data);
	free ((void *)ll);
}

static int _size (const LinkedList *ll) {
	Data *_data = (Data *)ll->self;
	return _data->size;
}

const LinkedList *LinkedList_create () {
	LinkedList *_linkedlist = NULL;
	Data *_data = (Data *)malloc (sizeof (Data));
	if (_data != NULL) {
		_data->head = NULL;
		_data->tail = NULL;
		_data->size = 0;

		_linkedlist = (LinkedList *)malloc (sizeof (LinkedList));
		if (_linkedlist != NULL) {
			_linkedlist->self = (void *)_data;
			_linkedlist->addLast = _addLast;
			_linkedlist->addFirst = _addFirst;
			_linkedlist->getLast = _getLast;
			_linkedlist->getFirst = _getFirst;
			_linkedlist->removeLast = _removeLast;
			_linkedlist->removeFirst = _removeFirst;
			_linkedlist->size = _size;
			_linkedlist->toArray = _toArray;
			_linkedlist->clear = _clear;
			_linkedlist->destroy = _destroy;
		} else 
			free (_data);
	}
	return _linkedlist;
}
