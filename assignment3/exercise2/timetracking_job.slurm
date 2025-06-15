#!/bin/bash

# Name of your job.
#SBATCH --job-name=false_sharing
#SBATCH --output=execution_time.log

# Allocate one task on one node and six CPUs for this task
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=6

# Allocate 12 Gigabytes for the whole node/task
#SBATCH --mem=12G
#SBATCH --exclusive

#SBATCH --time=00:10:00

export OMP_NUM_THREADS=6

# Run 10 iterations to measure execution time variability
for i in {1..10}
do
    time -f '%e' sleep 3
    echo "Iteration $i"

    # Run on 6 cores of the same processor
    export GOMP_CPU_AFFINITY="0,1,2,3,4,5"
    echo "false_sharing running on same processor cores: $GOMP_CPU_AFFINITY"
    
    time ./false_sharing 100000000

    # Run on 6 cores across different processors
    export GOMP_CPU_AFFINITY="0,2,4,6,8,10"
    echo "false_sharing running on different processor cores: $GOMP_CPU_AFFINITY"
    time ./false_sharing 100000000

    # Run on 6 cores of the same processor
    export GOMP_CPU_AFFINITY="0,1,2,3,4,5"
    echo "false_sharing_2 running on same processor cores: $GOMP_CPU_AFFINITY"
    time ./false_sharing_2 100000000

    # Run on 6 cores across different processors
    export GOMP_CPU_AFFINITY="0,2,4,6,8,10"
    echo "false_sharing_2 running on different processor cores: $GOMP_CPU_AFFINITY"
    time ./false_sharing_2 100000000
done
