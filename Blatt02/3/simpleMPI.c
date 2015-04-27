#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#ifndef
	#define PROCESSES = 1

int main(int argc, char** argv)
{
	rc = MPI_Init(&argc ,&argv);
	if(rc != MPI_SUCCESS)
	{
		printf("MPI could not be initialised\n");
		MPI_Abort(MPI_COMM_WORLD,rc);	
	}
	int threadID;
	MPI_Comm_rank(MPI_Comm_World, &rank);
	
	if(threadID == 0)
	{
		
	}
	else
	{
		
}	
	
	int* input = calloc(argc + 1, sizeof(int));
	int rest = argc % PROCESSES;
	if(rest != 0)
	{
