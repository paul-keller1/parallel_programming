#!/bin/bash

#SBATCH --job-name=hadamard
#SBATCH --output=hadamard.log
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --mem=12G
#SBATCH --exclusive
#SBATCH --time=40:00

# List of executables
executables=(
  "hadamard_omp_default"
  "hadamard_omp_auto"
  "hadamard_omp_static"
  "hadamard_omp_dynamic_1"
  "hadamard_omp_dynamic_4"
  "hadamard_omp_dynamic_8"
  "hadamard_omp_dynamic_100"
  "hadamard_omp_guided"
  "hadamard_omp_runtime"
)

# Problem sizes (N values)
Ns=(10000 20000 30000)

# Threads
threads=(1 4 8 12)


# Trials
trials=1

# Result file
result_file="benchmark_results.txt"
echo "Saving all results to $result_file"
echo "Executable,Problem_Size,Threads,Trial,Time(s)" > "$result_file"


# Run the serial executable first
for N in "${Ns[@]}"; do
  for ((trial=1; trial<=trials; trial++)); do
    echo "Running hadamard_serial with N=$N, Trial=$trial"
    output=$("./hadamard_serial" "$N" 2>&1 | grep "time:")
    time_value=$(echo "$output" | awk '{print $2}')
    
    # Write to result file
    echo "hadamard_serial,${N},1,${trial},${time_value}" >> "$result_file"
  done
done

# Run parallel executables
for exe in "${executables[@]}"; do
  for N in "${Ns[@]}"; do
    for t in "${threads[@]}"; do
      export OMP_NUM_THREADS=$t

      

      # Only for hadamard_omp_runtime: set OMP_SCHEDULE
      if [[ "$exe" == "hadamard_omp_runtime" ]]; then
        export OMP_SCHEDULE="GUIDED"
      else
	unset OMP_SCHEDULE
      fi
      
      for ((trial=1; trial<=trials; trial++)); do
        echo "Running $exe with N=$N, Threads=$t, Trial=$trial"
        output=$("./$exe" "$N" 2>&1 | grep "time:")
        time_value=$(echo "$output" | awk '{print $2}')
        
        # Write to result file
        echo "${exe},${N},${t},${trial},${time_value}" >> "$result_file"
      done
    done
  done
done

#help by gemini


