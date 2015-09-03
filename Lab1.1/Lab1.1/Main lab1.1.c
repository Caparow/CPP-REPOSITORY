#include <stdio.h>
#include <string.h>

int substr(const char *string1, const char *string2)
{
	int s, p, i;
	s = 0;

	for (i = 0; i <= strlen(string1); i++)
	{

		if (string1[i] == string2[0])
		{

			for (p = 0; p <= strlen(string2); p++)
				if (string1[i] == string2[p])
					i++;
				else
					break;

			if (p == strlen(string2) + 1)
			{
				s = i - p;
				break;
			}
		}
	}

	return(s);

}

int main()
{
	char  str1[30] = "";
	char  str2[10] = "";
	

	printf("Enter your first string: \n");
	gets(str1);

	printf("Enter your second string: \n");
	gets(str2);

	printf("Second string started at index # %d\n", substr(str1, str2));

	return 0;
}