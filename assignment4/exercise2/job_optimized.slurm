#!/bin/bash
#SBATCH --job-name=cache_analysis_optimized
#SBATCH --output=cache_analysis_optimized_%j.log
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1   # Single-threaded execution
#SBATCH --mem=12G
#SBATCH --exclusive

# filepath: /home/cb76/cb761035/assignment4/exercise2/job.slurm

# Output file for cache misses
CACHE_RESULTS_FILE="cache_results_optimized.txt"

# Write header just once
echo "Implementation, LLC-Load-Misses, LLC-Store-Misses" > "$CACHE_RESULTS_FILE"

echo "Running single-threaded cache analysis on optimized executables..."

# Function to run perf 5 times and compute the average cache misses
run_perf_test() {
    local executable=$1
    local total_load_misses=0
    local total_store_misses=0
    local runs=5

    echo "Testing $executable (optimized)..."

    for i in $(seq 1 $runs); do
        echo "  Run $i..."
        perf_output=$(perf stat -e LLC-load-misses,LLC-store-misses ./$executable 1 2>&1)
        load_misses=$(echo "$perf_output" | awk '/LLC-load-misses/ {gsub(",", "", $1); print $1}')
        store_misses=$(echo "$perf_output" | awk '/LLC-store-misses/ {gsub(",", "", $1); print $1}')

        # Ensure numbers are valid before adding
        if [[ -n "$load_misses" && -n "$store_misses" ]]; then
            total_load_misses=$((total_load_misses + load_misses))
            total_store_misses=$((total_store_misses + store_misses))
        fi
    done

    # Compute averages
    avg_load_misses=$((total_load_misses / runs))
    avg_store_misses=$((total_store_misses / runs))

    echo "$executable, $avg_load_misses, $avg_store_misses" >> "$CACHE_RESULTS_FILE"
}

# Run perf for optimized row-major and column-major implementations
run_perf_test "row_major_hadamard_optimized"
run_perf_test "column_major_hadamard_optimized"

# Run cachegrind for additional data (output is saved separately)
valgrind --tool=cachegrind --cache-sim=yes --cachegrind-out-file=cachegrind_row_optimized.out ./row_major_hadamard_optimized 1 > /dev/null 2>&1
cg_annotate cachegrind_row_optimized.out > row_major_cache_optimized.txt

valgrind --tool=cachegrind --cache-sim=yes --cachegrind-out-file=cachegrind_col_optimized.out ./column_major_hadamard_optimized 1 > /dev/null 2>&1
cg_annotate cachegrind_col_optimized.out > column_major_cache_optimized.txt

echo "Cache analysis completed. Results saved in $CACHE_RESULTS_FILE."
