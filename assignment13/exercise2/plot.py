import pandas as pd
import matplotlib.pyplot as plt
import os
from matplotlib.ticker import MaxNLocator

# Load both CSV files
df_remote = pd.read_csv("results.csv")
df_local = pd.read_csv("results_local.csv")

# Add a column to distinguish sources
df_remote["env"] = "remote"
df_local["env"] = "local"

# Combine data
df = pd.concat([df_remote, df_local], ignore_index=True)

# Extract snippet ID and optimization level
df["snippet"] = df["binary"].str.extract(r"(snippet\d+)")
df["opt_level"] = df["binary"].str.extract(r"_(O\d)")

# Create output directory
os.makedirs("plots", exist_ok=True)

# Loop through unique snippet names
for snippet in df["snippet"].unique():
    snippet_df = df[df["snippet"] == snippet]

    # Create a combined index: mode + env
    snippet_df["mode_env"] = snippet_df["mode"] + " (" + snippet_df["env"] + ")"

    # Pivot: index = mode+env, columns = opt level, values = avg time
    pivot_df = snippet_df.pivot(index="mode_env", columns="opt_level", values="avg_time_sec")

    # Ensure columns order O0, O3
    pivot_df = pivot_df[["O0", "O3"]]

    # Plot
    ax = pivot_df.plot(kind='bar', figsize=(8, 5), color=["#ff9999", "#66b3ff"])
    plt.title(f"{snippet} Execution Time: Local vs Remote, O0 vs O3")
    plt.ylabel("Average Time (seconds)")
    plt.xlabel("Mode (Environment)")
    plt.xticks(rotation=45, ha='right')

    # Tidy Y axis
    ax.yaxis.set_major_locator(MaxNLocator(nbins=8, prune='lower'))
    ax.grid(True, axis='y', linestyle="--", alpha=0.5)

    plt.tight_layout()

    # Save plot
    filename = f"plots/{snippet}_timing_compare.png"
    plt.savefig(filename, dpi=300)
    print(f"Saved: {filename}")
    plt.close()
