#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
	#define debug(x,...) printf(x,##__VA_ARGS__)
#else
	#define debug(x,...)
#endif

unsigned int faku(unsigned int n)
{
	debug("n is: %u\n",n);
	if(n == 1)
	{
		return 1;
	}
	else
	{
		return n * faku(n-1);
	}
}

int main(int argc, char** argv)
{
	unsigned int result = faku(15);
	printf("%u\n", result);
	return EXIT_SUCCESS;

}