#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc==1)
	{
		printf("This is the usage:\n enter a number element N \n");
	}
	else
	{
		printf("This is just some output unrelated to the number %s\n", argv[1]);
	}
}
