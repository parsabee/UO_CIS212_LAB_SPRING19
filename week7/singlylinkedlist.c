/*
 * author: Parsa Bagheri
 * a simple singly linked_list 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define UNUSED __attribute__((unused))

typedef struct node Node;
struct node {
	void *data;
	Node *next;
};

typedef struct data{
	int a;
	char name [256];
}Data;

Node *createNode (void *data) {
	Node *node = (Node *) malloc (sizeof (Node));
	if (node != NULL) {
		node->data = data;
		node->next = NULL;
	}
	return node;
}

void addNode (Node *head, Node *next) {
	Node *tmp = head;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = next;
}

void printList (Node *head) {
	for (Node *tmp = head; tmp != NULL; tmp = tmp->next){
		Data *dat = (Data *)(tmp->data);
		printf("%d, %s\n", dat->a, dat->name);
	}
}

void destroy_linkedlist (Node *head) {
	Node *tmp = head;
	while (tmp != NULL) {
		Node *tmp2 = tmp->next;
		free (tmp->data);
		free (tmp);
		tmp = tmp2;
	}
}

int main (UNUSED int argc, UNUSED char *argv[]) {

	Node *head = createNode((void *)1L);
	Data *dat = (Data *) malloc (sizeof (Data));
	dat->a = 0;
	strcpy (dat->name, "linkedList Head");
	head->data = dat;
	head->next = NULL;
	for (int i = 0; i < 4; i++) {
		Data *datNode = (Data *) malloc (sizeof (Data));
		datNode->a = i+1;
		strcpy(datNode->name, "linkedList Node");
		Node *node = createNode ((void *)datNode);
		addNode (head, node);
	}

	printList (head);
	destroy_linkedlist (head);
}