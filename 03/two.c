#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void getinput(char** lines, int* num, int* len);
int bin2dec(char* binary);
int criteria(char** input, int numLines, int len, bool oxygen);

void main()
{
	// read the input file
	char* lines[2000];

	int numLines = 0;
	int len;
	getinput(lines, &numLines, &len);

	int oxygen = criteria(lines, numLines, len, true);
	int co2 = criteria(lines, numLines, len, false);

	printf("%d\n", oxygen * co2);

	// cleanup
	for (int i = 0; i < numLines; i++)
	{
		free(lines[i]);
	}
}

int criteria(char** input, int numLines, int len, bool oxygen)
{
	int zeros = numLines;
	int rating = 0;

	char* lines[2000];
	memcpy(lines, input, sizeof(lines));

	for (int i = 0; i < (len - 1); i++)
	{
		int bits = 0;

		for (int j = 0; j < numLines; j++)
		{
			if (lines[j] == NULL) continue;

			char bit = lines[j][i];

			if (bit == '1')
				bits++;
		}

		// check most common
		char most = 0;
		if (bits >= (zeros - bits))
		{
			most = oxygen ? '1' : '0';
		}
		else
		{
			most = oxygen ? '0' : '1';
		}

		// null out the not-most values
		for (int j = 0; j < numLines; j++)
		{
			if (lines[j] == NULL) continue;

			char bit = lines[j][i];

			if (bit != most)
			{
				lines[j] = NULL;
				zeros--;
			}
			else
			{
				rating = bin2dec(lines[j]);
			}
		}
	}

	return rating;
}