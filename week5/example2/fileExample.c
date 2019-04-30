#include <stdlib.h>
#include <stdio.h>

#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]){
	char *fname = "input1.txt";
	char buf[2048];
	FILE *fp = NULL;
	
	int i;
	for(i = 0; i < 5; i++){
		fp = fopen(fname, "r");
		fgets(buf, sizeof buf, fp);
		fprintf(stdout, buf);
		fclose(fp);
	}
	
	return 0;
}
