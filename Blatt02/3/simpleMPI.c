#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#ifndef
	#define PROCESSES = 1
#endif

int main(int argc, char** argv)
{
	rc = MPI_Init(&argc ,&argv);
	if(rc != MPI_SUCCESS)
	{
		printf("MPI could not be initialised\n");
		MPI_Abort(MPI_COMM_WORLD,rc);	
	}
	
	int threadID;
	int numOfTasks;
	int recvBuf;
	int index = 0;
	
	MPI_Comm_rank(MPI_Comm_World, &threadID);
	MPI_Comm_size(MPI_Comm_World, &numOfTasks);
	
	if(threadID == 0)
	{
		int rest = argc - 1 % PROCESSES;
		int outBuf = {0,0};
		
		for(;index < numOfTasks;index++)
		{
			for(;index < rest;index++)
			{	
				outBuf[1]++;
				MPI_SEND(&outBuf,2,MPI_INT,index,0,MPI_Comm_World);
				outBuf[0]++;

			}
			MPI_SEND(&outBuf,2,MPI_INT,index,0,MPI_Comm_World);
		}
		index = 0;
		int sum = 0;
		for(;index < numOfTasks;index++)
		{
			int recvBufSum = 0;
			MPI_RECV(&recvBufSum,1,MPI_INT,index,MPI_Comm_World,MPI_STATUS_IGNORE);
			printf("Recieved %d from Process %d\n",recvBufSum,index);
			sum += recvBufSum;
		}
		printf("Total sum is: %d \n", sum);
	}

	index = 0;
	int sectionlength = ((argc - 1) / PROCESSES);

	MPI_RECV(&recvBuf,2,MPI_INT,0,MPI_Comm_World,MPI_STATUS_IGNORE);
	for(;index < PROCESSES; index++)
	{
		int sum = 0;
		indexk = (index * sectionlength) + recvBuf[0];
		for(;indexk < (index * sectionlength) + recvBuf[1];indexk++)
		{
			sum += argv[indexk+1];
		}
		MPI_SEND(&sum,1,MPI_INT,0,1,MPI_Comm_World);
	}

}	
	
	
