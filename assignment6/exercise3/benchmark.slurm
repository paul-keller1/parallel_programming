#!/bin/bash

#SBATCH --job-name=hadamard
#SBATCH --output=benchmark.log
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --mem=12G
#SBATCH --exclusive
#SBATCH --time=40:00

export OMP_NUM_THREADS=12
./hadamard_omp_default 32768



