#!/bin/bash

#SBATCH --time=1
#SBATCH -N 4 -n 4
#SBATCH --error=job.err --output=job.out

srun hostname
mpiexec ./a.out  1 1 1 1 1 1 1
