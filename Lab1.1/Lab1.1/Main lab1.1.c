#include <stdio.h>
#include <string.h>
#include "mystring.h"



int main()
{
	char  str1[30] = "";
	char  str2[10] = "";
	

	printf("Enter your first string: \n");
	gets(str1);

	printf("Enter your second string: \n");
	gets(str2);

	printf("Second string started at index #%d\n", substr(str1, str2));

	printf("Maximum number of similarities: %d\n ",  subseq(str1, str2));

	return 0;
}