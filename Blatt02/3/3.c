#ifdef DEBUG
	#define debug(x,...) printf(x,##__VA_ARGS__)
#else
	#define debug(x,...)
#endif

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		puts("ERROR: No numbers to sum up");
		return EXIT_FAILURE;
	}

	int process_ID;
	int num_Processes;
	int buffer[num_Processes * 2];
	int tag;
	int source;
	int destination;
	int *result;
	int current_Process_ID = 0;
	int final_Result = 0;
	MPI_Status status;


	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&num_Processes);
	MPI_Comm_rank(MPI_COMM_WORLD,&process_ID);
	int recvBuffer[2];
	
	if(process_ID==0)
	{
		debug("Start prepro\n");
		int offset = 0;
		int larger = 1;
		result = malloc(sizeof(int) * num_Processes);	
		int rest = (argc -1) % num_Processes;
		for(destination=0;destination < num_Processes; destination++)
		{
			if(rest==0) larger = 0;
			buffer[destination * 2 ] = offset;
			buffer[destination * 2 +1] = larger; 
			if(rest > 0)
			{	
				offset++;
				rest--;
			}
		}
		for(current_Process_ID = 0;current_Process_ID < num_Processes; current_Process_ID++)
		{
			debug("buffer of Process %d has %d and %d\n",
				current_Process_ID,buffer[current_Process_ID *2],
				buffer[current_Process_ID * 2 + 1]);
		}			
	}
	MPI_Scatter(buffer,2,MPI_INT,recvBuffer,2,MPI_INT,0,MPI_COMM_WORLD);
	debug("process %d got %d, %d \n",process_ID,recvBuffer[0],recvBuffer[1]);
	int length = (argc - 1) / num_Processes + recvBuffer[1];
	int start = 1 +(((argc - 1) / num_Processes) * process_ID) + recvBuffer[0];
	int current = start;
	int sum = 0;
	debug("start: %d\n",start);
	debug("	length: %d\n",length);
	debug("	argc: %d\n",argc);
	for(;current < start + length; current++)
	{	
		debug("	Process %d run %d\n",process_ID,current - start);
		debug("		argv[%d]: %ld\n",current,strtol(argv[current],NULL,10));
		sum += strtol(argv[current],NULL,10); 
	}
	debug("=> sum of Process %d: %d\n",process_ID , sum);
	MPI_Reduce(&sum,&final_Result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(process_ID == 0)
	{
//		debug("printing sums\n");
//		for(current_Process_ID = 0;current_Process_ID < num_Processes; current_Process_ID++)
//		{
//			printf("Process %d has sum and %d\n",
//			current_Process_ID,result[current_Process_ID]);
//			final_Result += result[current_Process_ID];
//		}
		printf("Final sum is: %d", final_Result);
	}	
	MPI_Finalize();
}
