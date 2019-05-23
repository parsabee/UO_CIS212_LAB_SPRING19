/*
 * Author: Parsa Bagheri
 * deque.h
 *
 * A simple implementation of the `deque' data structure
 * using a doubly linked-list
 */

#ifndef _DEQUE_H_
#define _DEQUE_H_
typedef struct deque Deque;

const Deque *Deque_create (void);
struct deque {
	void *self;
	int (*push_back)(const Deque *deque, void *element);
	int (*push_front)(const Deque *deque, void *element);
	int (*pop_back)(const Deque *deque, void **element);
	int (*pop_front)(const Deque *deque, void **element);
	int (*front)(const Deque *deque, void **element);
	int (*back)(const Deque *deque, void **element);
	long (*size)(const Deque *deque);
	void **(*toArray)(const Deque *deque, long *len);
	void (*clear)(const Deque *deque, void (*freeFxn)(void *));
	void (*destroy)(const Deque *deque, void (*freeFxn)(void *));
};

#endif /*_DEQUE_H_*/
