#!/bin/bash

#SBATCH --job-name=mandelbrot
#SBATCH --output=mandelbrot.log
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --mem=12G
#SBATCH --exclusive
#SBATCH --time=40:00

# Mandelbrot executables
executables=(
  "mandelbrot_omp_default"
  "mandelbrot_omp_static"
  "mandelbrot_omp_auto"
  "mandelbrot_omp_dynamic_1"
  "mandelbrot_omp_dynamic_4"
  "mandelbrot_omp_dynamic_8"
  "mandelbrot_omp_dynamic_100"
  "mandelbrot_omp_guided"
)

# Problem sizes (N values)
Ns=(10000)

# Threads
threads=(1 4 8 12)

# Trials
trials=1

# Result file
result_file="benchmark_results.txt"
echo "Saving all results to $result_file"
echo "Executable,Problem_Size,Threads,Trial,Time(s)" > "$result_file"

# --- Run Mandelbrot serial first ---
for N in "${Ns[@]}"; do
  for ((trial=1; trial<=trials; trial++)); do
    echo "Running mandelbrot_serial with N=$N, Trial=$trial"
    output=$("./mandelbrot_serial" "$N" 2>&1 | grep "time:")
    time_value=$(echo "$output" | awk '{print $2}')
    echo "mandelbrot_serial,${N},1,${trial},${time_value}" >> "$result_file"
  done
done

# --- Run Mandelbrot parallel executables ---
for exe in "${executables[@]}"; do
  for N in "${Ns[@]}"; do
    for t in "${threads[@]}"; do
      export OMP_NUM_THREADS=$t
      unset OMP_SCHEDULE

      for ((trial=1; trial<=trials; trial++)); do
        echo "Running $exe with N=$N, Threads=$t, Trial=$trial"
        output=$("./$exe" "$N" 2>&1 | grep "time:")
        time_value=$(echo "$output" | awk '{print $2}')
        echo "${exe},${N},${t},${trial},${time_value}" >> "$result_file"
      done
    done
  done
done



#had some help from gemini for this