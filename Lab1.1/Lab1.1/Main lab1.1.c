#include <stdio.h>
#include <string.h>
#include "mystring.h"



int main()
{
	char  str1[30] = "";
	char  str2[10] = "";
	char  pal[10] = "";
	char  pal2[15] = "";
	char *ppal2;
	char *npal;
	
	ppal2 = &pal2[0];

	printf("Enter your first string: \n");
	gets(str1);
	printf("\n");

	printf("Enter your second string: \n");
	gets(str2);
	printf("\n");

	printf("Second string started at index #%d\n\n", substr(str1, str2));

	printf("Maximum number of similarities: %d\n\n",  subseq(str1, str2));

	printf("Enter your string for polindrom check: \n");
	gets(pal);
	printf("\n");

	printf("Does theis string was palindrom? (1-Yes, 0-No): %d\n\n", ispal(pal));

	printf("Enter your string for polindrom solution: \n");
	gets(pal2);
	printf("\n");
	npal = makepal(ppal2);

	printf("Your palindrom : ");

	
	return 0;
}