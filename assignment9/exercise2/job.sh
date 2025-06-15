#!/bin/bash



# Name of the compiled binary
BIN="./flush"

# Number of trials
T=5

# Matrix size
N=40000

# Output file
OUTFILE="output.txt"
echo "" > "$OUTFILE"

export OMP_NUM_THREADS=12
export GOMP_CPU_AFFINITY=0-11

# Run serial initialization (no first-touch)
echo "========== Serial Initialization (no first-touch) ==========" >> "$OUTFILE"
for i in $(seq 1 $T); do
  echo "Trial: $i" >> "$OUTFILE"
  $BIN $N 0 >> "$OUTFILE"
done

# Run parallel initialization (first-touch)
echo "========== Parallel Initialization (first-touch) ==========" >> "$OUTFILE"
for i in $(seq 1 $T); do
  echo "Trial: $i" >> "$OUTFILE"
  $BIN $N 1 >> "$OUTFILE"
done
