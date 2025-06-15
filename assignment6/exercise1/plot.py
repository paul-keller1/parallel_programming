import subprocess
import matplotlib.pyplot as plt
import re
import os

# Config
executables = ["./critical", "./atomic", "./reduction"]
labels = ["critical", "atomic", "reduction"]
thread_counts = [1, 2, 4, 8, 12]
output_file = "execution_times.txt"  # Added output file name

# This will store the times
execution_times = {exe: [] for exe in executables}

# Run the executables
with open(output_file, "w") as f:  # Open file for writing
    for exe in executables:
        for threads in thread_counts:
            print(f"Running {exe} with {threads} threads...")
            f.write(f"Running {exe} with {threads} threads...\n")  # Write to file
            env = os.environ.copy()
            env["OMP_NUM_THREADS"] = str(threads)
            result = subprocess.run([exe], capture_output=True, text=True, env=env)
            output = result.stdout
            f.write(output) #write the program's output
            # Extract time from the output (you must print "time: ... seconds" in C program!)
            match = re.search(r"time:\s*([\d.]+)", output)
            if match:
                time = float(match.group(1))
                execution_times[exe].append(time)
                f.write(f"Time: {time} seconds\n")  # Write time to file
            else:
                print(f"Warning: Could not parse time for {exe} with {threads} threads.")
                f.write(
                    f"Warning: Could not parse time for {exe} with {threads} threads.\n"
                )  # Write warning to file

# Plotting
for exe, label in zip(executables, labels):
    plt.plot(thread_counts, execution_times[exe], marker='o', label=label)
plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (seconds)")
plt.title("Monte Carlo Pi Approximation - OpenMP Implementations")
plt.legend()
plt.grid(True)
plt.show()

# Save the plot to a file (optional)
plt.savefig("openmp_pi_plot.png")
