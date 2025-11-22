import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

csv_path = "./algorithm_results_converted.csv"
df = pd.read_csv(csv_path)

sizes = df["Input size"].str.split(".", expand=True)
df["N"] = sizes[0].astype(int)
df["Case"] = sizes[1]

algs = ["IS", "MS", "BMS", "QS", "RQS"]

slope_records = []

def plot_case(case_name, title, outfile):
    case_df = df[df["Case"] == case_name].copy().sort_values("N")
    x = np.log10(case_df["N"].values.astype(float))
    
    plt.figure()
    for alg in algs:
        y = np.log10(case_df[f"{alg} CPU time (s)"].values.astype(float))
        # Linear regression in log-log
        A = np.vstack([x, np.ones_like(x)]).T
        slope, intercept = np.linalg.lstsq(A, y, rcond=None)[0]
        slope_records.append({"Case": case_name, "Algorithm": alg, "Slope(log-log)": slope})
        # plt.plot(x, y, marker='o', label=f"{alg}  slope={slope:.2f}")
        plt.plot(x, y, marker='o', label=f"{alg}")
    plt.xlabel("Input Size (Log scale)")
    plt.ylabel("Time (Log scale)")
    plt.title(f"{title}")
    plt.legend()
    plt.grid(True, which='both', linestyle='--', linewidth=0.5)
    plt.tight_layout()
    plt.savefig(outfile, dpi=180)
    plt.show()

plot_case("case1", "Average Case (Case1)", "./figs/trend_case1.png")
plot_case("case2", "Best Case (Case2)", "./figs/trend_case2.png")
plot_case("case3", "Worst Case (Case3)", "./figs/trend_case3.png")
