#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"getBDD.h"


void displayColorLetter(char* word, char* try)
{
	for(int i=0;i<MAX_WORD_LENGTH-1;i++)
	{
		if(try[i]=='v')
		{
			printf("\e[0;32m");
			printf("%c ",word[i]);
		}
		else if(try[i]=='o')
		{
			printf("\e[0;33m");
			printf("%c ",word[i]);
		}
		else
		{
			printf("\e[0m");
			printf("%c ",word[i]);
		}
	}
	printf("\e[0m");
	printf("\n");
}



void generateBDD(char* input_file_name, char* output_file_name){
	FILE* file=NULL;
	FILE* output_file=NULL;
	file=fopen(input_file_name,"r");
	output_file=fopen(output_file_name,"w");
	char line[MAX_LINE_LEN];
	char tmpWord[6];
		for(char letter='A';letter<='Z';letter++)
		{
			char str[35];
			sprintf(str,"Wordle Words List Starting With %c\n",letter);
			while(fgets(line, MAX_LINE_LEN,file)!=NULL)
			{
				if(!strcmp(str, line))
				{
					fgets(line, MAX_LINE_LEN,file);
					fgets(line, MAX_LINE_LEN,file);

					char* token=strtok(line," ");

					while(token!=NULL)
					{
						if(strcmp(token,"\n"))
						{
							if(output_file!=NULL)
								fprintf(output_file,"%s\n",token);
							else
								printf("no output file");
						}
						token=strtok(NULL," ");
					}
				}
			}
			
			rewind(file);
		}
		fclose(file);
		fclose(output_file);
}

void getWord(char* bddName, char words[TOTAL_WORDS][MAX_WORD_LENGTH]){
	/*int randomIndex;
	srand(time(NULL));
	randomIndex=rand()%2310;*/
	FILE* bdd_file=NULL;
	bdd_file=fopen(bddName,"r");
	if(bdd_file==NULL)
	{
		printf("not able to open File");
		exit(0);
	}
	char word[MAX_WORD_LENGTH];
	int numWord=0;
	while(fgets(word,6,bdd_file)!=NULL && numWord<TOTAL_WORDS)
	{
		if (word[strlen(word) - 1] == '\n')
		{
            word[strlen(word) - 1] = '\0';
        }
    	if(strlen(word)>=MAX_WORD_LENGTH-1)
    	{
    		strcpy(words[numWord], word);
    		numWord++;
    	}
    }
}

int checkValidWord(char* word, char words[TOTAL_WORDS][MAX_WORD_LENGTH]){
	for(int i=0;i<TOTAL_WORDS;i++)
	{
		if(!strcmp(word,words[i]))
		{
			return 1;
		}
	}
	return 0;
}

void checkLetters(char* word,char* guess, char* try)
{
	int wordCount[26] = {0}; 
    int guessCount[26] = {0};

    for (int i = 0; i < MAX_WORD_LENGTH - 1; i++) {
        wordCount[word[i] - 'a']++;
        guessCount[guess[i] - 'a']++;
    }
	for(int i=0;i<MAX_WORD_LENGTH-1;i++)
	{
		if(word[i]==guess[i])
		{
			try[i]='v';
			wordCount[word[i] - 'a']--; 
            guessCount[guess[i] - 'a']--; 
		}
	}
	for (int i = 0; i < MAX_WORD_LENGTH - 1; i++) 
	{
        if (try[i] != 'v') { 
            if (wordCount[guess[i] - 'a'] > 0) 
            { 
                try[i] = 'o';
                wordCount[guess[i] - 'a']--;
            }
        }
    }
}
