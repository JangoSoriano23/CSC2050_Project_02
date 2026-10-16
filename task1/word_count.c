#include <stdio.h>
#include <stdlib.h>

void wc(FILE *fp) {
	//actual counters
	int wordcount = 0;
	int linecount = 0;
	int charcount = 0;

	//current letter
	int ch = fgetc(fp);
	int prevCh = ' ';
 
	while (ch != EOF) {
		//spaces, tabs, newlines, and other chars are counted for bytes
		charcount++;

		//if its a tab or space, then dont do whats in here it.
		if (ch != '\t' && ch != ' ') {
			//if its a newline, then add to linecount
			if (ch == '\n') {
				linecount++;
			//otherwise check the previous character to see if its a new word (counts as a new word if previous char is a whitespace)		
			} else if (prevCh == '\t' || prevCh == ' ' || prevCh == '\n') {
				wordcount++;
			}
		}	
		
		prevCh = ch;
		ch = fgetc(fp);
	}

	printf("\n%d lines, %d words, %d characters\n", linecount, wordcount, charcount);
}

int main(int argc, char *argv[]) {
	if (argc != 1 && argc != 2) {
		printf("Must have 1 text file or none\n");
		return 1;
	}
	
	//if there is 1 textfile do this
	if (argc == 2) {
		FILE *fp = fopen(argv[1], "r");

		//check if pointer is null
        	if (fp == NULL) {
                	printf("Could not open file for reading.\n");
                	return 1;
        	}
		wc(fp);
		fclose(fp);
	//otherwise, read from stdin
	} else {
		wc(stdin);
	}
	return 0;
}


