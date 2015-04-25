#include <stdlib.h>
#include <stdio.h>
int * createArray()
{
	int newArray[10];
	int index = 0;
	for(;index < 10; index++)
	{
		newArray[index] = index;
	}
	newArray[0] = 101;
	return newArray;
}
int * createArrayStatic()
{
	int * newArray = calloc(10,sizeof(int));
	newArray[0] = 100;
	return newArray;
}

int main(int argc, char** argv)
{
	int index = 0;
	int testArray[5];
	for(;index < 5;index++)
	{
		printf("%d\n",testArray[index]);
	}
	puts("");
	index = 0;
	for(;index < 5;index++)
	{
		testArray[index] = index + 1;
		printf("%d\n",testArray[index]);
	}
	puts("");
	

	char * charArray = malloc(sizeof(char)*10);
	index = 0;
	for(;index < 11; index++)
	{
		charArray[index] = 60 +index;
		printf("%c\n", charArray[index]);
	}

	int * array = createArray();
	printf("Array: %d\n", array[0] );

	int * staticArray = createArrayStatic();
	printf("StaticArray: %d\n", staticArray[0] );
	
	puts("END");

	return EXIT_SUCCESS;
}