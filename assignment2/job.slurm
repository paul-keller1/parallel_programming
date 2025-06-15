#!/bin/bash

# Name of your job.
#SBATCH --job-name=paulsspeedtest

#SBATCH --output=output.log

# Allocate one task on one node and six cpus for this task
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=6

# Allocate 12 Gigabytes for the whole node/task
#SBATCH --mem=12G

./medium
