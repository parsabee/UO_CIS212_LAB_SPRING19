/*
 * Author: Parsa Bagheri
 *
 * This is a simple version of the `cat' utility for demonstration purposes
 *
 * SYNOPSIS:
 * 		scat [-bns] [file ...]
 */

#include <stdio.h>
#include <string.h>

#define USAGE "usage: ./scat [-bns] [file ...]" /* usage string */
#define SIZE 2048 /* the maximum number of characters to read for each line */

int n_flag = 0; /* gets set if the n flag is specified */
int s_flag = 0; /* gets set if the s flag is specified */
int b_flag = 0; /* gets set if the b flag is specified */

void scat (FILE *fp) {
	/* scat takes a file pointer and prints the content of the file to stdout
	 * if the n flag is specified, the number of each line will be printed as well
	 */

	int line_num = 1;
	char line [SIZE];
	int is_empty_line = 0; /* this flag will be checked to see if we have adjacent empty lines */
	while (fgets (line, SIZE, fp) != NULL) {
		/* reading the file pointed to by `fp', line by line, and storing the content of each line
		 * in the `line' buffer above
		 */
		
		if (s_flag) {
			/* if s_flag is specified, we need to single space the output 
			 * (squeezing the adjacent empty lines to one single empty line) 
			 */

			if (strcmp (line, "\n") == 0) {
				/* if the line that we read is empty */

				if (is_empty_line == 0) { 
					/* if this flag wasn't set before, it gets set over here */
					
					is_empty_line = 1;
				}else {
					/* if it was set, then we can't print this line, because it's an empty line adjacet to another empty line */
					
					continue;
				}
			}else {
				/* the empty line streak is broken, we can now reset this flag */

				is_empty_line = 0;
			}
		}

		if (b_flag) {
			/* if b_flag is specified, we must not increament line_num */

			if (strcmp (line, "\n") != 0) {

				printf("%6d\t", line_num);
				line_num++;
			}
		}

		if (n_flag && !b_flag) {
			/* if n_flag is specified, we need to print the number of the lines */

			printf("%6d\t", line_num);
			line_num++; /* increment the line_num counter */
		}

		printf("%s", line);
		
	}
}

int main (int argc, char *argv[]) {
	/* main always takes two arguments, and they are the arguments passed to the program in command line
	 * an integer, argc (argument count)
	 * an array of char pointers (strings), argv(argument vector)
	 *
	 * in C and other compiled programming languages, your program has to always have a starting point
	 * `main' is the starting function
	 */

	FILE *fp = stdin;
	int i;
	for (i = 1; i < argc; i++) {
		/* initialize i with 1 and not 0, because index 0 argv[0] is the name of the program */
		
		if (argv[i][0] == '-') {
			/* it's a flag */

			int j;
			for (j = 1; argv[i][j] != '\0'; j++) {
				/* notice the `ending condition' of the above for loop, 
				 * your for loop doesn't necessarily end with a less than(<) condition,
				 * in this case, we are ending the for loop when we reach a null terminating character '\0'
				 */
				
				if (argv[i][j] == 'n') {
					/* user has specified the n flag, setting the global n_flag */

					n_flag = 1;
				}
				else if (argv[i][j] == 's') {

					s_flag = 1;
				}
				else if (argv[i][j] == 'b') {

					b_flag = 1;
				}
				else {
					/* if it's not the n or s flags, it can't be any other flag, so error */

					fprintf (stderr, "scat: illegal option -- %c\n", argv[i][1]);
					fprintf (stderr, "%s\n", USAGE);
					return 1;
				}
			}
		}

		else {
			/* now we are done parsing the flags, we should now go and parse the files */

			break;
		}
	}

	if (i == argc) {
		/* if we come here, then all of the arguments were flags and now we only need to parse stdin
		 * notice we set `fp' to be stdin previously, and we know that scat function takes a FILE * as it's argument,
		 * also we know that stdin is a file stream, so we can just pass that to our scat function
		 */
		scat (fp);
	}
	else {
		/* if we come here, then we have [a] file[s] to parse
		 */

		for (; i < argc; i++) {
			/* notice that the `initial statement' of the above for loop is empty and there's just a semicolon;
			 * in c, you don't have to have every field of a for loop filled, in fact this is a valid for loop: `for(;;)' (forever loop).
			 * since the initial statement of my forloop is empty, the value of i will just get carried over from the previous for loop.
			 */

			fp = fopen (argv[i], "r"); /* opening the file at index i, in the read mode `r' */
			if (fp != NULL) {
				/* after opening a file, you have to make sure that the file is open
				 * there can be cases where the program failed to open the file,
				 * or the file that the user specified does not exist,
				 * in these cases `fopen' returns NULL, so you have to check the return value of fopen and make sure it's not NULL
				 */

				scat (fp); /* performing the scat function on the file */
				fclose (fp); /* always close the file that you've opened */
			}

			else {
				/* if failed to open file
				 */

				fprintf(stderr, "scat: %s: No such file or directory\n", argv[i]);
				return 1;
			}
		}
	}

	return 0;
}