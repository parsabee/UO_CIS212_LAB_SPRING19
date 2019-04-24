#include <stdio.h>

/* This simple program has two functions besides main. Both of these functions had one error each
   and in class I used gdb to find these two errors. The errors in this version are removed.
   */

int len(char *word){
	int i = 0; // if we don't initialize i to be 0, i's value is indeterminate, i.e. there's no way to know what it will be.

	while(word[i] != '\0'){
		i++;
	}
	
	return i;
}

void print_reversed(char *word, int last_idx){
	int i;
	
	// the first character in the array of characters at position 0, 'h',  must also be printed out
	for(i = last_idx; i >= 0; i--){
		printf("%c", word[i]);
	}

	printf("\n");
}

int main(int argc, char * argv[]){
	char *word = argv[1];
	
	int length = len(word);

	printf("'%s' is %d characters long\n", word, length);

	print_reversed(word, length);
}
