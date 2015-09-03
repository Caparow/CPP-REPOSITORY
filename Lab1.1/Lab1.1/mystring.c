#include "mystring.h"


int substr(const char *string1, const char *string2)
{
	int s, p, i;
	s = 0;

	for (i = 0; i < strlen(string1); i++)
	{

		if (string1[i] == string2[0])
		{

			for (p = 0; p < strlen(string2); p++)
				if (string1[i] == string2[p])
					i++;
				else
					break;

			if (p == strlen(string2))
			{
				s = i - p;
				break;
			}
		}
	}

	return(s);

}

int subseq(const char *string1, const char *string2)
{
	int k, p, i, nk, ni, max;
	max = p = ni = 0;

	for (i = 0; i < strlen(string1); i++)
		for (k = 0; k < strlen(string2); k++)
		    {
		        if (string1[i] == string2[k])
		        {
		        	ni = i;
					for (nk = k; nk < strlen(string2); nk++)
					{
						if (string1[ni] == string2[nk])
						{
							p++;
							ni++;
						}
						else
							break;
					}
		            if (p > max)
			            max = p;
				    p = 0;				
			     }
		    }
	
	return(max);
}