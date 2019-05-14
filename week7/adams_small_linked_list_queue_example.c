#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node{
	struct node *next;
	char *name;
} Node;

typedef struct linkedList{
	Node *head;
	Node *tail;
	int length;
} LinkedList;

void print_queue(LinkedList *ll){
	Node *current;
	int i;
	char *prefix;

	for(current = ll->head, i = 0; current != NULL; current = current->next, i++){
		prefix = i == 0 ? "queue contents:\n\t" : "\t";
		printf("%s%i: %s\n", prefix, i, current->name);	
	}
}

void enqueue(LinkedList *ll, char *name){
	Node *new = (Node *)malloc(sizeof(Node));

	new->next = NULL;
	new->name = strdup(name);
	
	if (ll->length == 0)
		ll->head = new;
	else
		ll->tail->next = new;

	ll->tail = new;
	ll->length++;
	
	printf("enqueue'd %s\n", name);
}

char *dequeue(LinkedList *ll){
	char *name;
	name = strdup(ll->head->name);
	
	Node *head = ll->head;

	ll->head = ll->head->next;
	ll->length--;

	free(head);

	printf("dequeue'd %s\n", name);

	return name;
}

void destroy(LinkedList *ll){
	Node *p = ll->head;
	Node *temp;

	while(p != NULL){
		temp = p->next;
		free(p);
		p = temp;
	}

	free(ll);
}


int main(){
	LinkedList *ll1 = (LinkedList *)malloc(sizeof(LinkedList));
	
	ll1->head = NULL;
	ll1->tail = NULL;
	ll1->length = 0;
	
	enqueue(ll1, "Adam");
	enqueue(ll1, "Bob");
	enqueue(ll1, "Cooper");
	enqueue(ll1, "Davis");
	
	print_queue(ll1);

	dequeue(ll1);
	
	print_queue(ll1);
	
	enqueue(ll1, "Pegasus");
	dequeue(ll1);

	print_queue(ll1);

	destroy(ll1);

	return 0;
}
