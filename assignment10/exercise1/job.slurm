#!/bin/bash

#SBATCH --job-name=affinity_benchmark
#SBATCH --output=affinity_benchmark.log
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=6  # Request 6 CPUs for the 6 threads
#SBATCH --mem=2G
#SBATCH --time=00:05:00    # Set a reasonable time limit


EXECUTABLE="./atomic_increment"


OUTPUT_FILE="exercise1_times.txt"


echo "Affinity_Setting,Execution_Time(s)" > "$OUTPUT_FILE"

echo "Starting OpenMP Affinity Benchmarks..."

echo "Running with Default Affinity (OMP_NUM_THREADS=6)"
export OMP_NUM_THREADS=6
unset OMP_PLACES
unset OMP_PROC_BIND
OUTPUT=$("$EXECUTABLE" 2>&1 | grep "time:")
TIME_VALUE=$(echo "$OUTPUT" | awk '{print $2}')
echo "Default,${TIME_VALUE}" >> "$OUTPUT_FILE"
echo "  Time: ${TIME_VALUE}s"


echo "Running with OMP_PROC_BIND=spread (OMP_NUM_THREADS=6)"
export OMP_NUM_THREADS=6
export OMP_PROC_BIND=spread
unset OMP_PLACES 
OUTPUT=$("$EXECUTABLE" 2>&1 | grep "time:")
TIME_VALUE=$(echo "$OUTPUT" | awk '{print $2}')
echo "Spread,${TIME_VALUE}" >> "$OUTPUT_FILE"
echo "  Time: ${TIME_VALUE}s"


echo "Running with OMP_PROC_BIND=close (OMP_NUM_THREADS=6)"
export OMP_NUM_THREADS=6
export OMP_PROC_BIND=close
unset OMP_PLACES
OUTPUT=$("$EXECUTABLE" 2>&1 | grep "time:")
TIME_VALUE=$(echo "$OUTPUT" | awk '{print $2}')
echo "Close,${TIME_VALUE}" >> "$OUTPUT_FILE"
echo "  Time: ${TIME_VALUE}s"

echo "Running with OMP_PLACES=cores, OMP_PROC_BIND=close (OMP_NUM_THREADS=6)"
export OMP_NUM_THREADS=6
export OMP_PLACES=cores
export OMP_PROC_BIND=close
OUTPUT=$("$EXECUTABLE" 2>&1 | grep "time:")
TIME_VALUE=$(echo "$OUTPUT" | awk '{print $2}')
echo "Cores_Close,${TIME_VALUE}" >> "$OUTPUT_FILE"
echo "  Time: ${TIME_VALUE}s"
