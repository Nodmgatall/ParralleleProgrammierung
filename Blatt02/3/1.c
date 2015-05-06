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
	int buffer[2];
	int tag;
	int source;
	int destination;
	int *result;
	MPI_Status status;


	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&num_Processes);
	MPI_Comm_rank(MPI_COMM_WORLD,&process_ID);
	tag = 1337;
	source = 0;
	destination = 0;
	
	if(process_ID==0)
	{
		result = malloc(sizeof(int) * num_Processes);	
		buffer[0] = 0;
		buffer[1] = 1;
		int rest = (argc -1) % num_Processes;
		for(destination=0;destination < num_Processes; destination++)
		{
			if(rest==0) buffer[1] = 0;
			MPI_Send(&buffer,2,MPI_INT,destination,tag,MPI_COMM_WORLD);			
			if(rest > 0)
			{	
				buffer[0]++;
				rest--;
			}
		}
	}
	MPI_Recv(&buffer,2,MPI_INT,0,tag,MPI_COMM_WORLD,&status);
	debug("process %d got %d, %d \n",process_ID,buffer[0],buffer[1]);
	int length = (argc - 1) / num_Processes + buffer[1];
	int start = (((argc -1) / num_Processes) * process_ID) + 1 + buffer[0];
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
	if(process_ID == 0)
	{	
		printf("Process 0`s sum is: %d\n",sum);
		int recv_buffer = 0;
		int process_ID_recv = 1;
		//printf("num_Processes: %d\n",num_Processes);
		for(;process_ID_recv < num_Processes; process_ID_recv++)
		{
			MPI_Recv(&recv_buffer,1,MPI_INT,process_ID_recv,7331,MPI_COMM_WORLD,&status);	
			printf("Process %d`s sum is: %d\n",process_ID_recv,recv_buffer);
			sum += recv_buffer;
		}
		printf("Final sum is: %d\n",sum);
	}
	else
	{
		MPI_Send(&sum,1,MPI_INT,0,7331,MPI_COMM_WORLD);	
	}
	MPI_Finalize();
}
