#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getinput(char** lines, int* num, int* len);
int bin2dec(char* binary);

void main()
{	
	// read the input file
	char* lines[2000];

	int numLines = 0;
	int len;
	getinput(lines, &numLines, &len);

	// alloc strings for binary numbers
	char* rate = malloc(len);
	memset(rate, 0, len);

	char* epsilon = malloc(len);
	memset(epsilon, 0, len);

	// extract the data from binary
	for (int i= 0; i < (len - 1); i++)
	{
		int bits = 0;

		for (int j = 0; j < numLines; j++)
		{
			char bit = lines[j][i];

			if (bit == '1')
				bits++;
		}

		if (bits > (numLines - bits))
		{
			rate[i] = '1';
			epsilon[i] = '0';
		}
		else
		{
			rate[i] = '0';
			epsilon[i] = '1';
		}
	}

	printf("%d\n", bin2dec(rate) * bin2dec(epsilon));

	// memory go free!
	free(rate);
	free(epsilon);
	for (int i = 0; i < numLines; i++)
	{
		free(lines[i]);
	}
}