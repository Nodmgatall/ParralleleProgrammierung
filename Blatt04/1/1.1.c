#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
#define BILLION  1000000000L

int main(int argc, char** argv)
{
    int sum = 0;
    int strAsNumber = 0;
    struct timespec start, stop;
    clock_gettime( CLOCK_REALTIME, &start);
    int index;
    #pragma parallel omp for ordered
    for(index = 1;index < argc;index++)
    {	
	sscanf(argv[index], "%d", &strAsNumber );
    	printf("%d\n" , strAsNumber);
        sum += strAsNumber;
    }
    clock_gettime( CLOCK_REALTIME, &stop);
    printf("Sum: %d\n" , sum);
	printf("Time: %lf\n",
		 (double) (argc -1)/( stop.tv_sec - start.tv_sec ));
	return EXIT_SUCCESS;
}
