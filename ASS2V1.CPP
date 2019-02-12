#define FILENAME 32
#define EOF (-1)
#define WORDLENGTH 16
#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE *fpin;

void main (void)
{
	char inputfile[FILENAME], word[WORDLENGTH];
	char c, dummy;
	int place;

	printf("Text File Word Analyser\n");
	printf("\nPlease enter the name of the source file: ");
	gets(inputfile);
	while((fpin = fopen(inputfile, "r")) == NULL)
	{
		printf("That file does not exist, please enter another filename: ");
		gets(inputfile);
	}
	printf("Processing file :%s", inputfile);
	// Read in source file a word at a time
	do
	{
		place = 0;
		c = tolower(fgetc(fpin));
		while(c != ' ' && c != EOF)
		{
			if (c == '.' || c == ',' || c == '\n')
				dummy =  c;
			else
			{
				word[place] = c;
				place++;
			}
      c = tolower(fgetc(fpin));
		}
		word[place] = '\0';
      printf("\n%s",word);
	}while(c != EOF);
}
