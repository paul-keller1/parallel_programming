#!/bin/bash

# Set number of threads for OpenMP
export OMP_NUM_THREADS=2


# Run on 6 cores of the same processor
export GOMP_CPU_AFFINITY="6,7"
echo "false_sharing running on same processor cores: $GOMP_CPU_AFFINITY"
time ./false_sharing 100000000

# Run on 6 cores of the same processor
export GOMP_CPU_AFFINITY="6,7"
echo "false_sharing_2 running on same processor cores: $GOMP_CPU_AFFINITY"
time ./false_sharing_2 100000000

