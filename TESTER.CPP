/******************************************************************************/
/*					Text file writer																*/
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

FILE *fpout;
char numbers[MAXWORDS][10];
char outputfile[FILENAME];

void main (void)
{

	char reply, dummy;
	int n;

	printf("Text File writer\n");
	for(n = 0;n < MAXWORDS; n++)
		{
			itoa(n, numbers[n],10); // Convert numbers to string not ANSI
		}
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
	for(n = 0; n < MAXWORDS; n++)
		fprintf(fpout, "%s ", numbers[n]);
	fprintf(fpout, "%s", numbers[MAXWORDS]);
	fclose(fpout);
	printf("\n\nOutput file successfully written");
}
