import matplotlib.pyplot as plt
import pandas as pd

# Function to read and parse the data from a .txt file
def parse_data(file_path):
    df = pd.read_csv(file_path)
    return df

# Plotting function
def plot_data(df):
    # Manually define the executables you want to plot
    executables = [
        "mandelbrot_serial",
        "mandelbrot_omp_default",
        "mandelbrot_omp_auto",
        "mandelbrot_omp_static",
        "mandelbrot_omp_dynamic_1",
        "mandelbrot_omp_dynamic_4",
        "mandelbrot_omp_dynamic_8",
        "mandelbrot_omp_dynamic_100",
        "mandelbrot_omp_guided",
        "mandelbrot_omp_runtime"
    ]

    for exe in executables:
        plt.figure(figsize=(10, 6))
        
        subset_exe = df[df['Executable'] == exe]
        if subset_exe.empty:
            continue  # Skip if executable not found

        problem_sizes = subset_exe['Problem_Size'].unique()

        for N in problem_sizes:
            subset_N = subset_exe[subset_exe['Problem_Size'] == N]

            # Special case for mandelbrot_serial: only plot Threads=1
            if exe == "mandelbrot_serial":
                subset_N = subset_N[subset_N['Threads'] == 1]  

            plt.plot(subset_N['Threads'], subset_N['Time(s)'], marker='o', label=f'N={N}')

        plt.title(f'Execution Time vs Threads for {exe}')
        plt.xlabel('Number of Threads')
        plt.ylabel('Execution Time (s)')
        plt.legend(title='Problem Size')
        plt.grid(True)
        plt.tight_layout()
        plt.savefig(f"{exe}.png")

# Example file path
file_path = 'benchmark_results.txt'

# Parse the data
df = parse_data(file_path)

# Plot
plot_data(df)

#help by gemini
