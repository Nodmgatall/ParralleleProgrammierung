#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#ifndef PROCESSES
	#define PROCESSES 1
#endif

#ifdef DEBUG
	#define debug(x,...) printf(x,##__VA_ARGS__)
#else
	#define debug(x,...) 
#endif

int main(int argc, char** argv)
{
	int rc = MPI_Init(&argc ,&argv);
	if(rc != MPI_SUCCESS)
	{
		printf("MPI could not be initialised\n");
		MPI_Abort(MPI_COMM_WORLD,rc);	
	}
	debug("succes: rc = %d\n",rc);	
	int threadID;
	int numOfTasks;
	int *recvBuf;
	int index = 0;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &threadID);
	MPI_Comm_size(MPI_COMM_WORLD, &numOfTasks);
	
	debug("This is thread %d",threadID);
	if(threadID == 0)
	{
		int rest = argc - 1 % PROCESSES;
		int outBuf[2] = {0,0};
		
		for(;index < numOfTasks;index++)
		{
			for(;index < rest;index++)
			{	
				outBuf[1]++;
				MPI_Send(&outBuf,2,MPI_INT,index,0,MPI_COMM_WORLD);
				outBuf[0]++;

			}
			MPI_Send(&outBuf,2,MPI_INT,index,0,MPI_COMM_WORLD);
		}
		index = 0;
		int sum = 0;
		for(;index < numOfTasks;index++)
		{
			int recvBufSum = 0;
			MPI_Recv(&recvBufSum,1,MPI_INT,index,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			printf("Recieved %d from Process %d\n",recvBufSum,index);
			sum += recvBufSum;
		}
		printf("Total sum is: %d \n", sum);
	}
	debug("Proc %d is Starting\n",threadID);
	index = 0;
	int sectionlength = ((argc - 1) / PROCESSES);

	MPI_Recv(&recvBuf,2,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	for(;index < PROCESSES; index++)
	{
		int sum = 0;
		int indexk = (index * sectionlength) + recvBuf[0];
		for(;indexk < (index * sectionlength) + recvBuf[1];indexk++)
		{
			sum += strtol(argv[indexk+1],NULL,1);
		}
		MPI_Send(&sum,1,MPI_INT,0,1,MPI_COMM_WORLD);
	}

}	
	
	
