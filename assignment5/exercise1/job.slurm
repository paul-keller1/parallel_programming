#!/bin/bash
#SBATCH --job-name=cache_analysis
#SBATCH --output=cache_analysis_%j.log
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=6
#SBATCH --mem=12G
#SBATCH --exclusive


./ex1
./ex1_trials