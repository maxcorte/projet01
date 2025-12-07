from matplotlib import pyplot as plt
import pandas as pd

csv_file = "./question22.csv"


data = pd.read_csv(csv_file, skipinitialspace=True)

threads = [2, 4, 8, 16, 32]


means = data.mean(axis=1)
stds = data.std(axis=1, ddof=1)

# --- Plot ---
plt.figure(figsize=(12, 6))
plt.title("Temps d'exécution en fonction du nombre de threads (moyenne er écart-type)")
plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (secondes)")
plt.ylim(bottom=0)  
plt.ylim(0, 1)


plt.errorbar(
    threads,
    means,
    yerr=stds,
    fmt='o-',
    capsize=5,
    linewidth=2,
    label="moyenne et écart-type"
)

plt.xticks(threads)
plt.grid(True, linestyle="--", alpha=0.5)
plt.legend()

plt.savefig("question22.pdf")
plt.show()