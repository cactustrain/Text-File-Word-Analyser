#define FILENAME 32
#define EOF (-1)
#define WORDLENGTH 16
#define MAXWORDS 1000
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE *fpin;
char words[MAXWORDS][WORDLENGTH];
int frequency[MAXWORDS];

void main (void)
{
	char inputfile[FILENAME], word[WORDLENGTH];
	char c,  charcount, wordcount;
	int place, n, flag;

	charcount = wordcount = 0;
	printf("Text File Word Analyser\n");
	printf("\nPlease enter the name of the source file: ");
	gets(inputfile);
	while(!(fpin = fopen(inputfile, "r")))
	{
		printf("That file does not exist, please enter another filename: ");
		gets(inputfile);
	}
	printf("\nProcessing file %s", inputfile);
	// Read in source file splitting into words
	do
	{
		place = 0;
		while((c = tolower(fgetc(fpin))) != ' ' && c != EOF)
		{
			if (c != '.' && c != ',' && c != '\n')
				{
					word[place++] = c;
					charcount++;
				}
		}
		word[place] = '\0';
		// Now we have a word, check to see if on list and either store
		// or increase the count
		flag = FALSE; // This is set to true if a match is found
      n = 0;
		while(n < wordcount)
		{
		if (!strcmp(word,words[n]))
			{
				frequency[n]++;
				flag = TRUE;
				break;    // Exit loop early if match found
			}
		n++;
		}
		if (!flag)
		{
			frequency[wordcount] = 1;
			if (word[0] != '\0') // Happens when two spaces together in source file
				strcpy(words[wordcount++], word);
		}
	}while(c != EOF);
	fclose(fpin);
	for(n = 0; n < wordcount; n++)
		printf("\n%d occurence(s) of %s", frequency[n], words[n]);
	printf("\n%d characters in file", charcount);
}
