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

	printf("Does this string was palindrom? (1-Yes, 0-No): %d\n\n", ispal(pal));

	printf("Enter your string for polindrom solution: \n");
	gets(pal2);
	printf("\n");

	printf("Your palindrom : %s\n\n", makepal(ppal2));
	
	printf("Enter your string vector return: \n");
	gets(str1);
	printf("\n");
	
	int er=0;

	double* pb = txt2double(str1, &er);

	//if (er == 0)
	//	printf("Sorry but i can't do it becouse of your string: \n");
	//else
	printf("It's your vector? \n");
	for (int i = 0; i < er; i++)
		printf("%f", pb[i]);

	return 0;
}