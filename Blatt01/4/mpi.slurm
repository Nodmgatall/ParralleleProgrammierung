#!/bin/bash

#SBATCH --time=1
#SBATCH -N 2 -n 10
#SBATCH --error=job.err --output=job.out

srun hostname
mpiexec ./mpitest.x
