#!/bin/bash

#SBATCH --job-name=hadamard
#SBATCH --output=hadamard.log
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --mem=12G
#SBATCH --exclusive
#SBATCH --time=40:00

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

touch results.txt


echo -e "Exercise 1: " > results.txt

echo -e "Snippet 1: " >> results.txt
./snippet1 >> results.txt


echo -e "Snippet 2: " >> results.txt
./snippet2 >> results.txt


echo -e "Snippet 3: " >> results.txt
./snippet3 >> results.txt



