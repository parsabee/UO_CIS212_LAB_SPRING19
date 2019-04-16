/*
 * Author: Parsa Bagheri
 * 
 * This is a complete implementation of the `echo' program
 * SYNOPSIS
 *			./echo [-neE] [string ...]
 */

#include <string.h>
#include <stdio.h>

int n_flag = 0;
int e_flag = 0;

void printe (char *string) {
	/* when the e flag is specified, we need to interpret the `backslash escape' characters
	 * if the user inputs a string with backslash escape characters in the arguments of a program (argv),
	 * (e.g. echo "this is CIS 212\n", notice the last character '\n' is a backslash escape)
	 * the bash interprets backslashes '\' as two backslashes "\\", and two backslashes is a backslash escape character itself.
	 * therefore, there is need for a function that can reinterpret these characters
	 */

	int len = strlen(string);
	for (int j = 0; j < len; j++) {
		if (string[j] == '\\' && len != (j+1)) {
			switch (string[j+1]) {
				case '\'':
					printf("%c", '\'');
					break;
				case '\"':
					printf("%c", '\"');
					break;
				case '\\':
					printf("%c", '\\');
					break;
				case 'n':
					printf("%c", '\n');
					break;
				case 'r':
					printf("%c", '\r');
					break;
				case 't':
					printf("%c", '\t');
					break;
				case 'b':
					printf("%c", '\b');
					break;
				case 'f':
					printf("%c", '\f');
					break;
				case 'v':
					printf("%c", '\v');
					break;
				case '0':
					printf("%c", '\0');
					break;
				default:
					printf("\\%c", string[j+1]);
					break;
			}
			j++;
		}
		else
			printf("%c", string[j]);
	}
}

void echo (int i, int argc, char *argv[]) {

	if (i == argc) {
		if (!n_flag) 
			printf("\n");
	}
	else {
		for (; i < argc-1; i++){
			if (e_flag){
				printe(argv[i]);
				printf(" ");
			}
			else
				printf("%s ", argv[i]);
		}
		if (e_flag)
			printe(argv[argc-1]);
		else
			printf("%s", argv[argc-1]);
		if (!n_flag) 
			printf("\n");
	}
}

int main (int argc, char *argv[]) {

	int i;

	for (i = 1; i < argc; i++) {
		int flag = 0;

		if (argv[i][0] == '-') {
			flag = 1;
			int j;
			for (j = 1; argv[i][j] != '\0'; j++) {

				if (argv[i][j] == 'n') 
					n_flag = 1;

				else if (argv[i][j] == 'e') 
					e_flag = 1;

				else if (argv[i][j] == 'E') 			
					e_flag = 0;

				else {
					n_flag = 0;
					e_flag = 0;
					flag = 0;
					break;
				}
			}
		}

		if (!flag) 
			break;
	}

	echo (i, argc, argv);
	return 0;
} 