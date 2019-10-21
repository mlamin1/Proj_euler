#!/bin/bash

# File: prob1para.sh

#SBATCH --job-name=prob1para      
#SBATCH --ntasks=99
#SBATCH --mem=2gb
#SBATCH --time=00:00:30    # Time limit in the form hh:mm:ss
#SBATCH --output=out/%j.log

module load mpi/openmpi3-x86_64

# For a C MPI project
mpirun ~/cosc420/project/prob1parallel/prob1para
