#include <stdio.h>
#include <string.h>
#include "main.h"

/**
 * Entry point
 */
int main(int argc, char* argv[])
{
	arg(argv);

	return 0;
}

/**
 * Encode string to rot13
 */
char *stringEncode(char* string)
{
	char* stringRot13 = string;

	for (int i = 0; i < strlen(string); i++)
	{
		stringRot13[i] = charEncode(string[i]);
	}

	return stringRot13;
}

/**
 * Encode Char to rot13
 */
char charEncode(char Char)
{
	char rot13;

	/**
	 * Numbers
	 */
	if ('0' <= Char && Char <= '4')
	{
		rot13 = Char + 5;
	}
	else if('5' <= Char && Char <= '9')
	{
		rot13 = Char - 5;
	}
	/**
	 * MAJ
	 */
	else if('A' <= Char && Char <= 'M')
	{
		rot13 = Char + 13;
	}
	else if('N' <= Char && Char <= 'Z')
	{
		rot13 = Char - 13;
	}
	/**
	 * MIN
	 */
	else if('a' <= Char && Char <= 'm')
	{
		rot13 = Char + 13;
	}
	else if('n' <= Char && Char <= 'z')
	{
		rot13 = Char - 13;
	}
	else
	{
		rot13 = Char;
	}

	return rot13;
}

/**
 * Arg file or string
 */
void arg(char* argv[])
{
	
	if(strcmp(argv[1], "--file") || strcmp(argv[1], "-f"))
	{
		handle(argv[2]);
	}
	else
	{
		printf("%s", stringEncode(argv));
	}
}

/**
 * Conveting file to rot13
 */
void handle(char *path)
{
	FILE *input, *output;
	input = fopen(path, 'r');
	char *pathOut, c;

	if(!input)
	{
		printf("ERROR CANT OPEN FILE");
	}

	/**
	 * .txt case
	 */
	if (get_ext(path) == ".txt")
	{
		strncat(pathOut, path, 4);
		output = fopen(strcat("%s.rot13", pathOut), "w");

		//EOF END OF FILE
		while ((c = fgetc(input)) != EOF)
		{
			fputc(charEncode(c), output);
		}
		fclose(input);
		fclose(output);
	}
	/**
	 * .rot13 case
	 */
	else if(get_ext(path) == ".rot13")
	{
		strncat(pathOut, path, 6);
		fopen(strcat("%s.txt", pathOut), "w");

		//EOF END OF FILE
		while ((c = fgetc(input)) != EOF)
		{
			fputc(charEncode(c), output);
		}
		fclose(input);
		fclose(output);
	}
}

/**
 * get extension file
 */
const char *get_ext(const char *filename)
{
	const char* dot = strrchr(filename, '.');
	if (!dot || dot == filename)
	{
		return "";
	}
	return dot + 1;
}