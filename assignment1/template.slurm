#!/bin/bash


#SBATCH --partition=lva
#SBATCH --job-name test
#SBATCH --output=output.log
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive

/bin/hostname
