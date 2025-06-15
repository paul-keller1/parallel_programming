#!/bin/bash

# Name of the compiled binary
BIN="./ex1"

# Number of threads to test
THREADS=(1 2 4 6 12)

# Number of trials
TRIALS=5

# Matrix size
N=1500

# Output file

echo "" > output.txt


# Loop over thread counts
for t in "${THREADS[@]}"; do
    export OMP_NUM_THREADS=$t
    echo -e "" >> output.txt
    echo -e "$t Threads" >>output.txt
    for i in {1..5}; do
      echo  "Trial: $i " >>output.txt
      ./ex1 $N >> output.txt
    done

done
