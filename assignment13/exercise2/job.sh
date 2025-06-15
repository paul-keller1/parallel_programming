#!/bin/bash
#SBATCH --job-name=snippet_timing
#SBATCH --output=timing_output.log
#SBATCH --error=timing_error.log
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --mem=12G
#SBATCH --exclusive

echo "binary,mode,avg_time_sec" > results.csv

for opt in O0 O3; do
  for i in {1..7}; do
    binary=snippet${i}_${opt}
    if [[ -x "$binary" ]]; then
      echo "Running $binary 5 times..."
      total_orig=0
      total_opt=0
      runs=5

      for run in $(seq 1 $runs); do
        output=$(./"$binary")

        # Extract original and optimized times separately
        orig_time=$(echo "$output" | grep "Original time:"  | grep -Eo '[0-9]+\.[0-9]+')
        opt_time=$(echo "$output"  | grep "Optimized time:" | grep -Eo '[0-9]+\.[0-9]+')

        if [[ -n "$orig_time" && -n "$opt_time" ]]; then
          total_orig=$(echo "$total_orig + $orig_time" | bc -l)
          total_opt=$(echo "$total_opt + $opt_time" | bc -l)
        else
          echo "Warning: Missing time data from $binary run $run" >&2
        fi
      done

      avg_orig=$(echo "scale=10; $total_orig / $runs" | bc -l)
      avg_opt=$(echo "scale=10; $total_opt / $runs" | bc -l)

      # Record both modes
      echo "snippet${i}_${opt},original,${avg_orig}" >> results.csv
      echo "snippet${i}_${opt},optimized,${avg_opt}" >> results.csv
    else
      echo "$binary not found or not executable" >&2
    fi
  done
done
