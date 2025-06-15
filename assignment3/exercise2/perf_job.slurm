#!/bin/bash

# Name of your job.
#SBATCH --job-name=false_sharing
#SBATCH --output=output.log

# Allocate one task on one node and six CPUs for this task
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=6

# Allocate 12 Gigabytes for the whole node/task
#SBATCH --mem=12G
#SBATCH --exclusive

#SBATCH --time=00:10:00

export OMP_NUM_THREADS=6

# Simple timing test
/usr/bin/time -f '%e' sleep 5

# List available performance events (optional, but not needed for execution)
echo "Available performance events:"
perf list > perf_events.log  # Save to a file instead of printing

echo "Starting performance measurements..."

for program in false_sharing false_sharing_2
do
    for affinity in "0,1,2,3,4,5" "0,2,4,6,8,10"
    do
        export GOMP_CPU_AFFINITY="$affinity"
        echo "Running $program on cores: $GOMP_CPU_AFFINITY"
        
        # Measure performance
        perf stat -r 5 ./$program 100000000 #5 specifies the number of execution rounds
    done
done

echo "Performance tests completed."
