#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uniq(FILE *fp) {
	//check if pointer is null
	if (fp == NULL) {
		printf("filepointer is null\n");
		return;
	}
	
	//init vars for comparing and getline
	char *currline = NULL;
	char *prevline = NULL;
	size_t currsize = 0;

	//while theres still lines to read in the file repeat this
	while (getline(&currline, &currsize, fp) != -1) {
		//if its the first line or the new line is different than the old line, do this
		if (prevline == NULL || strcmp(currline, prevline) != 0) {
			printf("%s", currline);
			free(prevline);//free the old previous line
			prevline = currline; //assign the currentline to be the next previous line
			currline = NULL; //cut the pointer off so that its only attatched to prevline
			currsize = 0;
		} else {
			//otherwise if the previous line and current line are the same, just get rid of the currentline to compare to the next one
			free(currline);
                	currline = NULL;
			currsize = 0;
		}
	}

	//free the last prevline and currline now that we're out of the loop:)
	free(prevline);
	free(currline);
}

int main(int argc, char *argv[]) {
	if (argc != 1 && argc != 2) {
		printf("Must have 1 text file or none\n");
		return 1;
	}	

	//if there is one text file, do this
	if (argc == 2) {
		FILE *fp = fopen(argv[1], "r");
		if (fp == NULL) {
               	printf("Could not open file for reading.\n");
                	return 1;
		}
		uniq(fp);
		fclose(fp);
	} else {
	//otherwise read from stdin
		uniq(stdin);
	}
	
	return 0;
}
