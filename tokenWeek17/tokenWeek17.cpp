#include "stdafx.h"
#include <stdio.h>
#include "string.h"
#include "stdlib.h"

struct date
{
	int day, month, year;
};

struct record
{
	struct date orderDate;
	char region[20];
	char rep[20];
	char item[20];
	int units;
	float unitCost;
	float totalCost;
};

int nrecords = 0;
struct record records[501];
int readFile(char *fileName);
void findByRegion(char *region);
void findByRep(char *rep);
void findByItem(char *item);
void findByYear(int year);
void removeWhitespace(char *string);

int getOption();

void main()
{
	char string[20];
	char fileName[] = "C:\\Users\\sndri\\Documents\\Visual Studio 2015\\Projects\\tokenWeek17\\tokenWeek17\\SampleData.txt";
	int i = 0;
	int option, year;
	char temp[20];

	if (!readFile(fileName))
	{
		printf("File could not be opened !!\n");
		return;
	}

	option = getOption();


	while (option != 0)
	{
		switch (option)
		{
		case 1:
			puts("Enter Region");
			gets_s(temp);
			removeWhitespace(temp);
			_strlwr(temp);
			findByRegion(temp);
			break;
		case 2:
			puts("Enter Rep");
			gets_s(temp);
			removeWhitespace(temp);
			_strlwr(temp);
			findByRep(temp);
			break;
		case 3:
			puts("Enter Item");
			gets_s(temp);
			removeWhitespace(temp);
			_strlwr(temp);
			findByItem(temp);
			break;
		case 4:
			puts("Enter Year");
			gets_s(temp);
			year = atoi(temp);
			findByYear(year);
			break;
		}
		option = getOption();

	}
}

int readFile(char *fileName)
{
	FILE *ptr;
	ptr = fopen(fileName, "r");
	char delim[5] = "\t";
	char delim2[5] = "/";
	char line[200];
	char *token;

	if (ptr == NULL) return 0;


	do 
	{
		fgets(line, 199, ptr);
		if (strstr(line, "/"))
		{
			token = strtok(line, delim2);
			records[nrecords].orderDate.day = atoi(token);

			token = strtok(NULL, delim2);
			records[nrecords].orderDate.month = atoi(token);

			token = strtok(NULL, delim);
			records[nrecords].orderDate.year = atoi(token);

			strcpy(records[nrecords].region, strtok(NULL, delim));
			strcpy(records[nrecords].rep, strtok(NULL, delim));
			strcpy(records[nrecords].item, strtok(NULL, delim));

			_strlwr(records[nrecords].region);
			_strlwr(records[nrecords].rep);
			_strlwr(records[nrecords].item);

			token = strtok(NULL, delim);
			records[nrecords].units = atoi(token);

			token = strtok(NULL, delim);
			records[nrecords].unitCost = atof(token);
	
			token = strtok(NULL, delim);
			records[nrecords].totalCost = atof(token);
			nrecords++;
		}
	} while(!feof(ptr));

	return 1;
}


void findByRegion(char *region)
{
	int i = 0;
	float total = 0.0;

	for (i = 0; i<nrecords; i++)
	{
		if (!strcmp(records[i].region, region))
		{
			total = total + records[i].totalCost;
		}
	}
	printf("Sales for region: %s = %.2f\n", region, total);
}

void findByRep(char *rep)
{
	int i = 0;
	float total = 0.0;

	for (i = 0; i<nrecords; i++)
	{
		if (!strcmp(records[i].rep, rep))
		{
			total = total + records[i].totalCost;
		}
	}
	printf("Sales for rep: %s = %.2f\n", rep, total);
}

void findByItem(char *item)
{
	int i = 0;
	float total = 0.0;

	for (i = 0; i<nrecords; i++)
	{
		if (!strcmp(records[i].item, item))
		{
			total = total + records[i].totalCost;
		}
	}
	printf("Sales for item: %s = %.2f\n", item, total);
}

void findByYear(int year)
{
	int i = 0;
	float total = 0.0;

	for (i = 0; i<nrecords; i++)
	{
		if (records[i].orderDate.year == year)
		{
			total = total + records[i].totalCost;
		}
	}
	printf("Sales for year: 20%d = %.2f\n", year, total);
}

int getOption()
{
	int option = 0;
	char inp[3];

	puts("Enter one of the follow options:");
	puts("1 - sales by region");
	puts("2 - sales by rep");
	puts("3 - sales by item");
	puts("4 - sales by year");
	puts("0 - quit");
	gets_s(inp);
	option = atoi(inp);

	return option;
}

void removeWhitespace(char *string)
{
	char temp[100]; //store new string without whitespaces
	int i; 
	int end; 
	int start = 0;
	end = strlen(string) - 1; //finds the index of the end of the string

	while (string[start] == ' ') //records index of where the whitespaces stop of the start
	{
		start++;
	}
	
	while (string[end] == ' ') //records index of the last character before whitespace
	{
		end--;
	}

	for (i = 0; (end - start) >= i ; i++) //copies characters between the whitespaces
	{
		temp[i] = string[start + i]; //stores it in a temp as not to alter the original pointer
	}

	temp[i] = '\0'; //ends the new string
	strcpy(string, temp); //copies the new string into the same location as old string
}