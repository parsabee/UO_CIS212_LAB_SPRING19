#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

#define UNUSED __attribute__((unused))

#define USAGE "usage: ./print [-i] [file]\n"

typedef struct {
	int line_num;
	char *line;
}LineInfo;

void freeFxn (void *element) {
	LineInfo *li = (LineInfo *)element;
	free (li->line);
	free (li);
}

void print (const Deque *deque, int inverse) {
	LineInfo *element;
	int (*pop)(const Deque*, void **);
	pop = (inverse) ? (deque->pop_back) : (deque->pop_front);
	while (pop (deque, (void **)&element)) {
		printf ("%d\t%s", element->line_num, element->line);
		free (element->line);
		free (element);
	}	
}

int main (UNUSED int argc, UNUSED char *argv[]) {
	int inverse = 0;
	int i;
	FILE *fp = stdin;
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (strlen (argv[i]) > 2){
				fprintf (stderr, "invalid option: %s\n", argv[i]);
				fprintf (stderr, "%s", USAGE);
				return 1;
			
			}	
			if (argv[i][1] == 'i')
				inverse = 1;
			else {
				fprintf (stderr, "invalid option: %c\n", argv[i][1]);
				fprintf (stderr, "%s", USAGE);
				return 1;
			}
		}
		else 
			break;
	}
	
	if (i < argc) {
		fp = fopen (argv[i], "r");
		if (!fp) {
			fprintf (stderr, "no such file or directory: %s\n", argv[i]);
			fprintf (stderr, "%s", USAGE);
			return 2;
		}
	}

	const Deque *deque = Deque_create ();
	if (deque) {
		char line [BUFSIZ];
		for (int i = 1; fgets (line, BUFSIZ, fp); i++) {
			LineInfo *li = (LineInfo *)malloc (sizeof (LineInfo));
			if (li) {
				li->line_num = i;
				char *tmp = strdup (line);
				if (tmp){
					li->line = tmp;
					if (!(deque->push_back (deque, (void *)li))) {
						free (tmp);
						free (li);
						goto clean_up;
					}
				}
				else {
					free (li);
					goto clean_up;
				}
			}
			else 
				goto clean_up;
		}
		print (deque, inverse);
	}
clean_up:
	if (deque)
		deque->destroy(deque, freeFxn);
	return 0;
}
