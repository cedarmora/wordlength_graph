/* Takes words from standard input, counts how many words of each lengths there are, and displays a vertical histogram of the results.
 *
 * Possible improvements: 
 * 	1: Make the height scalable, so that if there are more than GRAPH_HEIGHT - 1 results for a single length, it can display them. 
 * 	2: Separate graph array creation from graph printing. 
 * 	3: Maybe pointers will help? 
 * 	4: Do the whole file, not just the SAMPLE_SIZE. 
 * 	5: Use file input, not standard/keyboard input. */

#include <stdio.h>

#define MAX_WORD_LENGTH 41
#define SAMPLE_SIZE 75
#define GRAPH_HEIGHT 26
#define IN 1
#define OUT 0

int getwordlength();
void graph(int s[]);

int main()
{
	/* Last index of wordlengthfreq is used for words larger than MAX_WORD_LENGTH - 1. */
	int wordlengthfreq[MAX_WORD_LENGTH];
	int i;
	int lengthindex;
	
	/* Not using index 0, since no words are length 0. */
	for (i = 1; i < MAX_WORD_LENGTH; ++i) 
		wordlengthfreq[i] = 0;
	
	for (i = 0; i < SAMPLE_SIZE; ++i) {
		lengthindex = getwordlength();
		if (lengthindex < 0)
			continue;
		/* If the word is larger than the largest word size, given in MAX_WORD_LENGTH, sets it to be at the last index of wordlengthfreq,
		 * which should be MAX_WORD_LENGTH - 1. */
		if (lengthindex >= MAX_WORD_LENGTH)
			lengthindex = MAX_WORD_LENGTH - 1;
		++wordlengthfreq[lengthindex];
	}

	graph(wordlengthfreq);
	return 0;
}

/* Returns a single word's length from the standard input. */
int getwordlength()
{
	int c;
	int wordlength = 0;
	int state = OUT;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (state == IN)
				return wordlength;
			continue;
		}
		state = IN;
		++wordlength;
	}
	return -1; /* If function fails, this will run. */
}

void graph(int s[])
{
	int i, j;
	               /*    AKA x/i        AKA y/j */
	int grapharray[MAX_WORD_LENGTH][GRAPH_HEIGHT];

    /* Initializing to 0/false */
	for (i = 1; i < MAX_WORD_LENGTH; ++i) {
		for (j = 1; j < GRAPH_HEIGHT; ++j) {
			grapharray[i][j] = 0;
		}
	}

    /* Building the graph */
	for(i = 1; i < MAX_WORD_LENGTH; ++i) {
		for (j = 1; j <= s[i] && j < GRAPH_HEIGHT; ++j) {
			grapharray[i][j] = 1;
		}
	}

	puts("\nWord length is x axis, word length frequency is y axis.");
	     /* index of top/last element. */
	for (j = GRAPH_HEIGHT - 1; j > 0; --j) {
		for (i = 1; i < MAX_WORD_LENGTH; ++i) {
			if (i == 1)
				printf("%2d", j);
			printf("%4c", grapharray[i][j] == 1 ? '-' : ' ') ;
			if (i == MAX_WORD_LENGTH - 1)
				putchar('\n');
		}
	}
	
	printf("  ");
	for (i = 1; i < MAX_WORD_LENGTH; ++i) {
		printf("%4d", i);
	}

	putchar('\n');
}
