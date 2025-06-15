import matplotlib.pyplot as plt
import numpy as np

# Updated data from output.txt
data = {
    1: [29.48, 29.46, 29.38, 29.47, 29.38],
    2: [14.95, 14.73, 14.60, 14.64, 14.76],
    4: [7.44, 7.35, 7.43, 7.54, 7.41],
    6: [5.14, 5.14, 5.12, 5.29, 5.15],
    12: [2.66, 2.60, 2.57, 2.60, 2.62]
}

threads = sorted(data.keys())
trials = len(next(iter(data.values())))

# Calculate average times per thread count
avg_times = [np.mean(data[t]) for t in threads]

plt.figure(figsize=(10, 6))

# Plot individual trials
for t in threads:
    plt.plot(range(1, trials+1), data[t], marker='o', label=f'{t} Threads')

# Plot average times as horizontal dashed lines
for t, avg in zip(threads, avg_times):
    plt.hlines(avg, 1, trials, colors='gray', linestyles='dashed', alpha=0.5)

plt.xticks(range(1, trials+1))
plt.xlabel('Trial')
plt.ylabel('Time (seconds)')
plt.title('Execution Time by Threads and Trial')
plt.legend(title='Threads')
plt.grid(True)
plt.tight_layout()

plt.savefig('performance_graph_debugged_version.png', dpi=300)