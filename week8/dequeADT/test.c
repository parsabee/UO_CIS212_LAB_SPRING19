#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define UNUSED __attribute__((unused))
int main (UNUSED int argc, UNUSED char *argv[]) {
	FILE *fp = stdin;
	int status = 0;
	const Deque *deque1 = Deque_create ();
	if (!deque1)
		return 1;
	const Deque *deque2 = Deque_create ();
	if (!deque2) {
		deque1->destroy(deque1, NULL);
		return 1;
	}
	//for testing destroy with free
	const Deque *deque3 = Deque_create ();
	if (!deque3) {
		deque1->destroy(deque1, NULL);
		deque2->destroy(deque2, NULL);
		return 1;
	}

	char buf [BUFSIZ];
	while (fgets (buf, BUFSIZ, fp)) {
		//testing push_back and push_front methods
		char *str1 = strdup (buf);
		if (!str1){
			status = 1;
			goto clean_up;
		}
		char *str2 = strdup (buf);
		if (!str2){
			free (str1);
			status = 1;
			goto clean_up;
		}
		//push_back to deque1
		if (! (deque1->push_back (deque1, str1))) {
			free (str1);
			free (str2);
			status = 1;
			goto clean_up;
		}
		//push_front to deque2
		if (! (deque2->push_front (deque2, str1))) {
			free (str1);
			free (str2);
			status = 1;
			goto clean_up;
		}
		if (! (deque3->push_back (deque3, str2))) {
			free (str1);
			free (str2);
			status = 1;
			goto clean_up;
		}
		
	}
	fprintf (stderr, "[SUCCESS]: push_back() and push_front()\n");
	
	//testing back and front methods
	char *str1, *str2;
	deque1->back (deque1, (void **)&str1);
	deque2->front (deque2, (void **)&str2);
	if (strcmp (str1, str2)) {
		fprintf (stderr, "[TEST FAIL]: front() and back()\n%s != %s\n", str1, str2);
		status = 1;
		goto clean_up;
	}
	fprintf (stderr, "[SUCCESS]: back() and front()\n");
	
	long len;
	void **array = deque3->toArray (deque3, &len);
	if (!array) {
		status = 1;
		goto clean_up;
	}

	//testing pop_back and pop_front mehtods
	while (1) {
		int hasNext;
		hasNext = deque1->pop_back (deque1, (void **)&str1);
		hasNext = deque2->pop_front (deque2, (void **)&str2);
		if (!hasNext)
			break;

		if (strcmp (str1, array[--len])){
			fprintf (stderr, "[TEST FAIL]: toArray()\n");
			status = 1;
			free (str1);
			goto clean_up;
		}
		if (strcmp (str1, str2)) {
			fprintf (stderr, "[TEST FAIL]: pop_front() and pop_back()\n%s != %s\n", str1, str2);
			status = 1;
			free (str1);
			goto clean_up;
		}
		free (str1);
	}
	fprintf (stderr, "[SUCCESS]: pop_back() and pop_front()\n");

clean_up:
	deque1->destroy (deque1, NULL);
	deque2->destroy (deque2, NULL);	
	fprintf (stderr, "[SUCCESS]: destroy(NULL), no segmentaion fault, run with valgrind for memory report\n");
	deque3->destroy (deque3, free);
	free (array);
	fprintf (stderr, "[SUCCESS]: destroy(free), no segmentaion fault, run with valgrind for memory report\n");
	if (status) 
		fprintf (stderr, "[FAIL]: didn't pass all test cases\n");
	return status;
}
