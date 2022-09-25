#include<stdio.h>
#include<stdlib.h>

int str_len(char* arr)
{
	int i = 0;
	while (arr[i+1] != '\0')
		++i;

	return i;
}

int comparison(char* arr1, char* arr2, char letter)
{
	int i = 0;
	while (i < str_len(arr1))
	{
		if (arr1[i] != arr2[i])
			return 0;
		++i;
	}
	if (arr2[i] != ' ' || arr2[i + 1] != letter)
		return 0;
	return 1;
}

void copy(char* arr1, char* arr2)
{
	int i = 0;
	while (arr2[i] != '>')
		++i;
	int k = 0;
	while (arr2[i + 2 + k] != '\0')
	{
		arr1[k] = arr2[i + 2 + k];
		++k;
	}
	arr1[k] = '\0';
}

int main(int argc, char* argw[])
{
	
	FILE* F;
	F = fopen(argw[argc - 2], "rt");
	if (F == NULL)
	{
		perror("fopen failed.");
		return 1;
	}
	printf("File opened.\n");

	int lines_count = 0;           
	int charters_count = 1;			
	int max_charters_count = 0;     
	
	
	while (!feof(F) && !ferror(F))
	{
		if (fgetc(F) == '\n')
		{
			charters_count = 0;
			lines_count++;
		}
		++charters_count;
		if (charters_count > max_charters_count)
			++max_charters_count;
	}
	max_charters_count += 1;
	fseek(F, 0, SEEK_SET);          

	char** text = malloc(lines_count * sizeof(char*));
	if(text == NULL)
	{
		perror("malloc_text failed.");
		return 1;
	}
	for (int i = 0; i < lines_count; ++i)
	{
		text[i] = malloc(max_charters_count * sizeof(char));
		if (text[i] == NULL)
		{
			perror("malloc_text[i] failed.");
			return 1;
		}
	}
	
	for (int i = 0; i < lines_count; ++i)
	{
		fflush(stdin);
		fgets(text[i], max_charters_count, F);
		if(feof(F))
			break;
	}
	fclose(F);
	
	printf("\n");

	for (int i = 0; i < lines_count; ++i)
	{
		printf("Line number %d: %s", i + 1, text[i]);
	}
	printf("\n");

	int i = 0;
	printf("%s", text[0]);
	while (argw[2][i] != '\0')
	{
		for (int j = 1; j < lines_count; ++j)
		{
			if (comparison(text[0], text[j], argw[2][i]) == 0 && j == lines_count - 1)
			{
				printf("There is no suitable command.");
				return 0;
			}
			if (comparison(text[0], text[j], argw[2][i]) == 1)
			{
				copy(text[0], text[j]);
				printf("%s", text[0]);
				j = lines_count;
			}
		}
		++i;
	}
	return 0;
}