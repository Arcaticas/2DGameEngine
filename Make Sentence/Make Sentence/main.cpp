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


const char* MakeSentence(char* i_strings[])
{

	int word = 0;
	int letter = 0;
	int size = 0;
	while (i_strings[word][0] != '\0')
	{
		letter = 0;
		while (i_strings[word][letter] != '\0')
		{
			size++;
			letter++;

		}
		size++;
		word++;

	}

	char* sentence = reinterpret_cast<char*>(malloc(size * sizeof(char)));
	const char* ret;
	
	bool first = true;
	word = 0;
	if (sentence)
	{
		while (i_strings[word][0] != '\0')
		{
			letter = 0;

			while (i_strings[word][letter] != '\0')
			{
				if (first)
				{
					*sentence = toupper(i_strings[word][letter]);
					first = false;
				}
				else
				{
					*sentence = i_strings[word][letter];

				}
				letter++;
				sentence++;


			}
			*sentence = ' ';
			sentence++;
			word++;
		}
		sentence--;
		*sentence = '.';
		sentence++;
	}

	
	sentence -= size;




	ret = sentence;
	free(sentence);

	return ret;
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
		 const char* word = gets_s(Input, lenInput);

		//check input is blank
		if (Input[0] == '\0') 
		{
			//add a null character word
			temp = stringSentence;
			size++;
			stringSentence = reinterpret_cast<char**>(malloc(size * sizeof(char*)));

			if (stringSentence)
			{
				for (int i = 0; i < size; i++)
				{
					if (i == size - 1)
					{
						stringSentence[size - 1] = reinterpret_cast<char*>(malloc(sizeof(char)));
						if(stringSentence[size-1])
							stringSentence[size - 1][0] = '\0';
					}
					else
					{
						stringSentence[i] = temp[i];
					}
				}
			}
			//break out of loop
			free(temp);
			break;
		}
		//if not the first time, copies strings to temp pointer
		if (stringSentence != nullptr) 
		{
			temp = stringSentence;
		}
		//increment the number of words in a sentence
		size++;
		//count the length of that word
		int count = 0;
		//nullptr check
		if (word != nullptr)
		{
			while (word[count++] != '\0')
				;
		}
		
		//allocate memory for the bigger sentence pointer
		stringSentence = reinterpret_cast<char**>(malloc(size * sizeof(char*)));
		//nullptr check
		if (stringSentence != nullptr)
		{
			for (int i = 0; i < size; i++)
			{
				//if the last element in the array, add the newest word
				if (i == size - 1)
				{
					//allocate memory for the new word
					stringSentence[size - 1] = reinterpret_cast<char*>(malloc(count * sizeof(*word)));
					//nullptr check
					if (word != nullptr)
					{
						//assign the chars
						for (int j = 0; j < count; j++)
						{
							if(stringSentence[i])
								stringSentence[i][j] = word[j];
						}
					}

				}
				//copys over the older words to the new, larger sentence pointer.
				else
				{
					stringSentence[i] = temp[i];
				}
			}
			//free temp pointer
			free(temp);
		}
	}
	

	/*Currently this is just a test to see if I am storing the user input strings correctly.
	  So far, It does seem to work as it usually outputs the right strings, but I consistantly
	  am getting heap corruption of some kind and dont understand where its coming from.
	for(int i = 0; i < size; i++)
	{
		int count = 0;
		while (stringSentence[i][count]!='\0')
		{
			std::cout << stringSentence[i][count];
			count++;
		}
		std::cout << "\n";
	}*/
	

	printf(MakeSentence(stringSentence));

	// free the memory it allocated.
	if (stringSentence)
	{
		for (int i = 0; i < size; i++)
		{
			free(stringSentence[i]);
		}
		free(stringSentence);
	}
	

	// in a Debug build check for memory leaks.
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	return 0;

}