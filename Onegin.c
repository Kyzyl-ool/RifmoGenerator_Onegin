#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------
//! Checks if character is punctuation sign
//!@param	c				Character
//!@return					If c is character, returns 1. Else - 0.
//----------------------------------------------------------------------
int IsPunctuation(char c);

//----------------------------------------------------------------------
//! Reads text file.
//! @param 	filename 		File name
//! @return 				Pointer to the beginning of the text array
//----------------------------------------------------------------------
char* readfile(const char* filename);

//----------------------------------------------------------------------
//!Counts amount of strings
//!@param	s				String
//!@return 					Amount of strings
//----------------------------------------------------------------------
int amount_of_strings(const char* s);

//----------------------------------------------------------------------
//!Makes an array of the strings separated by '\n'.
//!@param	s				Sequence of characters
//!@return					Pointer to the array of the strings
//----------------------------------------------------------------------
char** make_array_of_strings_beginnings(char* s);

//----------------------------------------------------------------------
//!Replaces '\n' to '\0' in sequence of characters
//!@param	s				Sequence of characters
//----------------------------------------------------------------------
void replace_slashN_to_slashZero(char* s);

//----------------------------------------------------------------------
//!Compares two strings from end.
//!@param	s1				First string
//!@param	s2				Second string
//!@return					Returns 1, if s1 > s2. Else returns 0.
//----------------------------------------------------------------------
int compare_letters_from_end(char* s1, char* s2);

//----------------------------------------------------------------------
//!Counts amount of characters in string
//!@param	s				String
//!@return					Amount of characters
//----------------------------------------------------------------------
int string_length(char* s);

//----------------------------------------------------------------------
//!Sorts array of strings from end
//!@param array_of_strings	Array of strings
//!@param amount			Amount of strings in array
//----------------------------------------------------------------------
void sort_array_of_strings(char** array_of_strings, int amount);

//----------------------------------------------------------------------
//!Prints array of strings
//!@param	array			Array of strings
//!@param	n				Amount of strings in array
//----------------------------------------------------------------------
void print_array_of_strings(char** array, int n);

//----------------------------------------------------------------------
//!Swaps two strings in array
//!@param array_of_strings	Array of strings
//!@param i					Number of first string
//!@param j					Number of second string
//----------------------------------------------------------------------
void swap_two_char_adresses(char** array_of_strings, int i, int j);

int main(int argc, char** argv)
{
	printf("String sorter program.\n");
	if (argc != 2)
	{
		printf("Incorrect amount of input arguments.\n");
	}
	assert(argv[1]);
	char* file_name = argv[1];
	
	char* text = readfile(file_name);
	int amount = amount_of_strings(text);
	char** strings_beginnings = make_array_of_strings_beginnings(text);
	replace_slashN_to_slashZero(text);
	sort_array_of_strings(strings_beginnings, amount);
	print_array_of_strings(strings_beginnings, amount);
	return 0;
}

char* readfile(const char* filename)
{
	assert(filename);
	FILE* fi = fopen(filename, "r");
	assert(fi); //IF,  см №3
	
	fseek(fi, 0, SEEK_END);
	char* text = (char*)malloc(ftell(fi)*sizeof(char));
	assert(text != NULL);
	
	fseek(fi, 0, SEEK_SET);
	int i = 0;
	char c = fgetc(fi);
	while (c != EOF)
	{
		text[i] = c;
		i++;
		c = fgetc(fi);
	}
	fclose(fi);
	return text;
}

int amount_of_strings(const char* s)
{
	assert(s != NULL);
	int i = 0, n = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\n') i++;
		while (s[i+1] == '\n') i++;
		n++;
		i++;
	}
	return n;
}

char** make_array_of_strings_beginnings(char* s)
{
	assert(s != NULL);
	
	char** strings = (char**)malloc(amount_of_strings(s)*sizeof(char*));
	assert(strings);
	
	strings[0] = s;
	int i = 0, j = 1;
	while (s[i] != '\0')
	{
		while (s[i] != '\n') i++;
		while (s[i+1] == '\n') i++;
		strings[j] = &s[i+1];
		i++;
		j++;
	}
	return strings;
}

void replace_slashN_to_slashZero(char* s)
{
	assert(s != NULL);
	
	int i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\n') i++;
		s[i] = '\0';
		i++;
	}
}

int IsPunctuation(char c)
{
	if (
	c == ',' ||
	c == ' ' ||
	c == ';' ||
	c == '?' ||
	c == '-' ||
	c == '.' ||
	c == ':' ||
	c == ')' ||
	c == '"' ||
	c == '!' ||
	c == '\'')
		return 1;
	else
		return 0;
}

int compare_letters_from_end(char* s1, char* s2)
{
	assert(s1 != NULL); assert(s2 != NULL);
	int n1 = string_length(s1), n2 = string_length(s2);
	int delta = n1 - n2;
	int i = n1 - 2;
	while (IsPunctuation(s1[i]))
	{
		i--;
		delta--;
	}
	while (IsPunctuation(s2[i-delta]))
	{
		delta++;
	}
	while (i >= 0)
	{
		if (s1[i] > s2[i-delta]) return 1;
		else if (s1[i] < s2[i-delta]) return 0;
		i--;
	}
	return 1;
}

int string_length(char* s)
{
	assert(s != NULL);
	int i = 0;
	while(s[i] != '\0')
	{
		i++;
	}
	return i+1;
}

void sort_array_of_strings(char** array_of_strings, int amount)
{
	for (int i = amount - 2; i >= 0; i--)
	{
		for (int j = 0; j <= i; j++)
		{
			if (strcmp(array_of_strings[j], array_of_strings[j+1]))
			{
				swap_two_char_adresses(array_of_strings, j, j+1);
			}
			/*if (string_length(array_of_strings[j]) > string_length(array_of_strings[j+1]))
			{
				if (compare_letters_from_end(array_of_strings[j], array_of_strings[j+1])) swap_two_char_adresses(array_of_strings, j, j+1);
			}
			else
			{
				if (compare_letters_from_end(array_of_strings[j+1], array_of_strings[j])) swap_two_char_adresses(array_of_strings, j, j+1);
			} */
		}
	}
}

void print_array_of_strings(char** array, int n)
{
	for (int i = 0; i < n; i++) printf("%s\n", array[i]);
}

void swap_two_char_adresses(char** array_of_strings, int i, int j)
{
	char* tmp = array_of_strings[i];
	array_of_strings[i] = array_of_strings[j];
	array_of_strings[j] = tmp;
}
