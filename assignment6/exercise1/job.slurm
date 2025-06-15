#!/bin/bash
#SBATCH --job-name=pi_calc
#SBATCH --output=pi_calc.out
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:10:00
#SBATCH --mem=12G
#SBATCH --exclusive



export OMP_NUM_THREADS=1
./critical 1
export OMP_NUM_THREADS=2
./critical 2
export OMP_NUM_THREADS=4
./critical 4
export OMP_NUM_THREADS=8
./critical 8
export OMP_NUM_THREADS=12
./critical 12



/bin/hostname
