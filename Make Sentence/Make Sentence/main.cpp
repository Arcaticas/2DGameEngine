#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>
#include <crtdbg.h>
#else
#include <stdlib.h>
#include <stdio.h>
#endif // _DEBUG
#include <iostream>
char* MakeSentence(char** input, int size)
{
	// convert i_strings to a complete char string sentence, with spaces between words and a . at the end and a '\0' terminator.
	// allocate only the memory needed for the above.

	char* r = (char*)malloc(sizeof(char*));
	int length = 0;
	if (input&&r) {
		for (int i = 0; i < size; i++)
		{
			int count = 0;
			if (input[i])
			{		
				while (*input[i] != '\0')
				{
					r[length] = *input[i];
					length++;
					count++;
					input[i]++;
				}
				input[i] -= count;
			}

			if (i == size - 1)
			{
				r[length] = '.';
				length++;
				r[length] = '\0';
				length++;
			}
			else
			{
				r[length] = ' ';
				length++;

			}
		}
	}

	return r;
}

int main(int i_argc, char** i_argl)
{
	// a temporary input buffer.
	const size_t	lenInput = 128;
	char			Input[lenInput];
	int size = 0;
	char** stringSentence = nullptr;
	char** temp = nullptr;

	while (true) 
	{
		// ask the user for a word.
		printf("Enter a word for the sentence, empty to end: ");
		char* word = gets_s(Input, lenInput);
		//check input is blank
		if (Input[0] == '\0') 
		{
			break;
		}
		//if not the first time, copies strings to temp pointer
		if (stringSentence != nullptr) 
		{
			temp = stringSentence;
		}
		//increment the size of the sentence
		size++;
		//allocate memory for the bigger sentence pointer
		stringSentence = (char**)malloc(size * sizeof(char*));
		if (stringSentence != nullptr)
		{
			for (int i = 0; i < size; i++)
			{
				//if the last element in the array add the newest word
				if (i == size - 1)
				{
					//allocate memory for the new word
					stringSentence[size - 1] = (char*)malloc(sizeof(word));
					int count = 0;
					if (word != nullptr)
					{
						while (*word != '\0')
						{
							if (stringSentence[i])
							{
								stringSentence[i][count] = *word;
							}
							count++;
							word++;
						}
					}
					if(stringSentence[i])
					{
						stringSentence[i][count] = '\0';
					}
				}
				else
				{
					stringSentence[i] = temp[i];
				}
			}
			//free temp pointer
			free(temp);
		}
	}
	/*
	for(int i = 0; i < size; i++)
	{
		while (*stringSentence[i]!='\0')
		{
			std::cout << *stringSentence[i];
			stringSentence[i]++;
		}
		std::cout << '\n';
	}
	*/
	// a sample set of words
	const char* test[] = {
		"This",
		"is",
		"a",
		"test",
		NULL
	};
	// MakeSentence() is the function we need to implement.
	// it should take in an array of words and create a sentence,
	// allocating EXACTLY enough memory for the resultant string.
	// it should use malloc() to allocate the memory.
	// it can use no other CRT or STL functions.
	// print out the sentence
	if(stringSentence!=nullptr)
		printf(MakeSentence(stringSentence, size));

	// free the memory it allocated.

	for (int i = 0; i < size; i++)
	{
		free(stringSentence[i]);
	}

	free(stringSentence);

	// in a Debug build check for memory leaks.
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;

}