#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stringADT.h"
#include "arraylist.h"
#include "iterator.h"

/*
 * Author: PARSA BAGHERI
 *
 * SYNOPSIS:
 *
 * 	./wrodperline [-lp] [file ...]
 *
 * */


#define USAGE "./wordperline [-lp] [file ...]"

typedef struct flags {
	int p_flag;
	int l_flag;
}Flags;

void wordperline (FILE *fp, Flags *fl) {
	
	char line [BUFSIZ];
	const String *str = String_create("");
	if (str == NULL)
		return;

	while (fgets (line, BUFSIZ, fp) != NULL) {
		str->clear (str);
		if (fl->p_flag) {
			
			int len = strlen (line);
			for (int i = 0; i < len; i++) {
			
				if (ispunct (line [i]) || line [i] == '\n')
					line [i] = ' ';
			}
		}

		str->append (str, line);	
		if (fl->l_flag)
			str->lower(str);
		const ArrayList *al = str->split (str, "");
		if (al != NULL) {
			
			long size  = al->size (al);
			for (long i = 0; i < size; i++) {
			
				char *word;
				(void) al->get(al, i, (void **) &word);
				printf ("%s\n", word);
			}
			al->destroy(al, free);
		}
	}

	str->destroy(str);
	return;
}

int main (int argc, char *argv[]) {
	
	Flags *flags = (Flags *)malloc(sizeof(Flags));
	if (flags == NULL) {
		fprintf (stderr, "malloc failure\n");
		return 2;
	}
	flags->l_flag = flags->p_flag = 0;

	int i;
	for (i = 1; i < argc; i++) {
	
		if (argv[i][0] == '-') {
			int j;
			for (j = 1; argv[i][j] != '\0'; j++) {
				switch (argv[i][j]) {
					case 'p':
						flags->p_flag = 1;
						break;
					case 'l':
						flags->l_flag = 1;
						break;
					default:
						fprintf (stderr, "wordperline: illegal option -- %c\n", argv[i][j]);
						return 3;
				}
			}
		}
		else
			break;
	}

	FILE *fp = stdin;
	if (i == argc) 
		wordperline (fp, flags);

	else {
		for (; i < argc; i++) {
			fp = fopen (argv[i], "r");
			if (fp != NULL) {
				wordperline (fp, flags);
				fclose (fp);
			}
			else {
				fprintf (stderr, "%s: no such file or directory\n", argv[i]);
				return 3;
			}
		}
	}
	free (flags);
	return 0;
}
