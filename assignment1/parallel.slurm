#!/bin/bash

# Name of your job.
#SBATCH --job-name=name

# Allocate one task on one node and six cpus for this task
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=6 // cpus used for parallelisation

# Allocate 12 Gigabytes for the whole node/task
#SBATCH --mem=12G

# it is no longer necessary to tell OpenMP how many software threads to start
####    export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
./your_openmp_executable
