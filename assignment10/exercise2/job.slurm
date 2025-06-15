#!/bin/bash
#SBATCH --job-name=delannoy
#SBATCH --output=delannoy_%j.log
#SBATCH --cpus-per-task=12
#SBATCH --exclusive
#SBATCH --time=20:00

export OMP_NUM_THREADS=1
./delannoy 12 > delannoy_seq.txt

export OMP_NUM_THREADS=12
./delannoy 12 > delannoy_par.txt
