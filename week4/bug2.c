#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This simple example program takes a word from the user as an argument passed on the 
   command line. It then takes the array of characters, allocates enough space on the 
   heap for the characters, and copies the array of characters onto the heap. After printing out
   the string, the space on the heap is free'd. This example was used in class to illustrate valgrind's 
   basic functionality.
   */

char *place_on_heap(const char *word){
	char *ptr = (char *)malloc(sizeof(char)*(strlen(word)+1)); // need to add one to make room for the null terminator, '\0'
	strcpy(ptr, word);
	return ptr;
}

void remove_from_heap(char *word){
	free(word);
}

int main(int argc, char *argv[]){
	const char *word1 = argv[1];
	
	char *word2 = place_on_heap(word1);

	printf("%s\n", word2);

	remove_from_heap(word2);

	//free(word2); // if we try to free again, valgrind will complain because we have a allocation/free imbalance
}
