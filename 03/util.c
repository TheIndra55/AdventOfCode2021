#include <stdio.h>
#include <stdlib.h>

// converts a binary number to decimal
int bin2dec(char* binary)
{
	int len = strlen(binary);
	long dec = 0;

	int j = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		if (binary[i] != '1' && binary[i] != '0') continue;

		int multiply = 1 << j++;

		if (binary[i] == '1')
		{
			dec += multiply;
		}
	}

	return dec;
}

// reads input.txt and returns all lines
void getinput(char** lines, int* num, int* len)
{
	FILE* file;

	// MSVC don't likey fopen
	fopen_s(&file, "input.txt", "r");

	char line[100];
	int i = 0;
	while (fgets(line, 100, file))
	{
		char* text = malloc(100);
		strcpy(text, line);

		lines[i++] = text;
		*len = strlen(text);
	}

	*num = i;

	fclose(file);
}