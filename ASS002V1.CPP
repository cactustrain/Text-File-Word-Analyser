/******************************************************************************/
/*																										*/
/*					Student : Michael Russell  Date: 20 January 2000					*/
/*					Assignment Number 2(a)  -  Text File Word Analyser					*/
/*					Module: Introduction to programming (No. 18)							*/
/*					BTEC HND Software Engineering  -  Group 2								*/
/*					Tutor: R.M Brown																*/
/*																										*/
/******************************************************************************/
#define BELL '\a'
#define FILENAME 32
#define EOF (-1)
#define WORDLENGTH 16
#define MAXWORDS 1000
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

FILE *fpin, *fpout; // file pointers
char words[MAXWORDS][WORDLENGTH];
int frequency[MAXWORDS];
void swaps(char [WORDLENGTH], char [WORDLENGTH]);
void swapn(int, int);

void main (void)
{
	char inputfile[FILENAME], outputfile[FILENAME], word[WORDLENGTH];
	char c, reply, dummy;
	int place, n, totalwords, charcount, wordcount, found;
	void sort(int, char [MAXWORDS][WORDLENGTH], int [WORDLENGTH]);

	charcount = wordcount = totalwords = 0;
	printf("Text File Word Analyser\n");
	printf("\nPlease enter the name of the source file: ");
  	gets(inputfile);
	while(!(fpin = fopen(inputfile, "r")))
	{
		putchar(BELL);
		printf("That file does not exist, please enter another filename: ");
		gets(inputfile);
	}
	printf("\nProcessing file %s....", inputfile);
	// Read in source file splitting into words separated by spaces
	do
	{
		place = 0;
		while(place == 0)
		{
			while((c = tolower(fgetc(fpin))) != ' ' && c != EOF && c != '.' && c != ',' && c != '\n')
			{
				if(place == 15)
				{
					printf("\nWord too long in %s, aborting conversion", inputfile);
					exit(0); // Terminate program, shutting all files
				}
				// No need for an else statement here
				word[place++] = c;
				charcount++;
			}
		}
		word[place] = '\0';
		//if (word[0] != '\0') // Happens when two separators together in source file
			totalwords++;
		// Now we have a word, check to see if on list and either store
		// or increase the count
		found = FALSE; // This is set to true if a match is found
      n = 0;
		while(n < wordcount)
		{
			if (!strcmp(word, words[n]))
			{
				frequency[n]++;
				found = TRUE;
			}
		n++;
		}
		if (!found)
		{
			if (wordcount < 1000)
			{
				frequency[wordcount] = 1;
				//if (word[0] != '\0') // Happens when two separators together in source file
					strcpy(words[wordcount++], word);
			}
			else
			{
				 printf("\nToo many words in %s, terminating input now", inputfile);
				 c = EOF;
			}
		}
	}while(c != EOF);
	fclose(fpin);
	printf("\nSorting into order");
   // Sort the data
	sort(wordcount, words, frequency);
	printf("\nSorted");
	// Send data to output file
	reply = 'n';
	while (reply == 'n')
	{
		printf("\nPlease enter the name of the output file: ");
		gets(outputfile);
		if((fpout = fopen(outputfile, "r")))
		{
			putchar(BELL);
			do{
			printf("\nThat file already exists, overwrite? (Y or N) ");
			}while((reply = tolower(getchar())) != 'n' && reply != 'y');
			if(reply == 'n')
				fclose(fpout);
			else
				 reply = 'y';
			dummy = getchar();  // dispose of unwanted return character
		}
		else
			reply = 'y';
	}
	fclose(fpout);
	printf("\nNow writing output file...");
	fpout = fopen(outputfile, "w");
	fprintf(fpout, "Input file: %s\n", inputfile);
	for(n = 0; n < wordcount; n++)
	{
		fprintf(fpout, "\n%d occurrence%s", frequency[n], frequency[n] == 1 ? "" : "s");
		fprintf(fpout, " of %s", words[n]);
	}
	fprintf(fpout, "\n\nWord count =%d", totalwords);
	if (charcount)
		fprintf(fpout, "\nAverage number of characters =%d", charcount / totalwords);
	fclose(fpout);
	printf("\n\nOutput file successfully written");
}

// Functions

void sort(int wc, char w[][WORDLENGTH], int f[])
{
		int flag, tempstr, n;
		char temp[WORDLENGTH];

do{
		flag =  FALSE;
		for (n = 0; n < wc - 1; n++)
		{
			if (strcmp(words[n], words[n + 1]) > 0)
			{
				swaps(words[n+1], words[n]);
				swapn(frequency[n], frequency[n + 1]);
				flag = TRUE;
			}
		}
	}while(flag == TRUE);
return;
}
void swaps(char a[], char b[])
{
	char temp[WORDLENGTH];

	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
	return;
}
void swapn(int a, int b)
{
	int temp;

	temp = a;
	a = b;
	b = temp;
	return;
}
