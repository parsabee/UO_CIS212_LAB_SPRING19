#include <stdio.h>
#include <string.h>

typedef struct{
	FILE * fp;
	char fn[100]; //space for the file name
} MyFile;

int main(int argc, char* argv[]){
	MyFile files[5]; //create five element array in which each element is a MyFile structure 

	int i, n_files = 0;

	for(i = 1; i < argc; i++){
		files[n_files].fp = fopen(argv[i], "r"); //get names for files from argv and open each one 
		strcpy(files[n_files].fn, argv[i]);
		n_files ++;
	}

	for(i = 0; i < n_files; i++){
		printf("%s\n", files[i].fn);
	}
}	



