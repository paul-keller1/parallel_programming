import pandas as pd
import matplotlib.pyplot as plt
import os
from matplotlib.ticker import MaxNLocator

# Load CSV file
df = pd.read_csv("results.csv")

# Create output directory
os.makedirs("plots", exist_ok=True)

# Extract snippet ID and optimization level
df["snippet"] = df["binary"].str.extract(r"(snippet\d+)")
df["opt_level"] = df["binary"].str.extract(r"_(O\d)")

# Loop through unique snippet names
for snippet in df["snippet"].unique():
    snippet_df = df[df["snippet"] == snippet]

    # Create a pivot for plotting
    pivot_df = snippet_df.pivot(index="mode", columns="opt_level", values="avg_time_sec")

    # Sort columns to ensure O0 then O3
    pivot_df = pivot_df[["O0", "O3"]]

    # Plot
    ax = pivot_df.plot(kind='bar', figsize=(6, 4), color=["#ff9999", "#66b3ff"])
    plt.title(f"{snippet} Execution Time: Original vs Optimized")
    plt.ylabel("Average Time (seconds)")
    plt.xlabel("Mode")
    plt.xticks(rotation=0)

    # Use cleaner Y-axis ticks
    ax.yaxis.set_major_locator(MaxNLocator(nbins=8, prune='lower'))  # Up to 8 clean ticks
    ax.grid(True, axis='y', linestyle="--", alpha=0.5)

    plt.tight_layout()

    # Save plot
    filename = f"plots/{snippet}_timing.png"
    plt.savefig(filename, dpi=300)  # High resolution
    print(f"Saved: {filename}")
    plt.close()
