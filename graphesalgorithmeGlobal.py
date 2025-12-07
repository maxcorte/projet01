from matplotlib import pyplot as plt
import pandas as pd

csv_file_TAS = "./part2/question22/question22.csv"
csv_file_TATAS = "./part2/question23/question23.csv"


dataTAS = pd.read_csv(csv_file_TAS, skipinitialspace=True)
dataTATAS = pd.read_csv(csv_file_TATAS, skipinitialspace=True)

threads = [2, 4, 8, 16, 32]


meansTAS = dataTAS.mean(axis=1)
stdsTAS = dataTAS.std(axis=1, ddof=1)

meansTATAS = dataTATAS.mean(axis=1)
stdsTATAS = dataTATAS.std(axis=1, ddof=1)

# --- Plot ---
plt.figure(figsize=(12, 6))
plt.title("Temps d'exécution en fonction du nombre de threads (moyenne er écart-type)")
plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (secondes)")
plt.ylim(bottom=0)  
plt.ylim(0, 1)

plt.errorbar(
    threads,
    meansTATAS,
    yerr=stdsTATAS,
    fmt='o-',
    capsize=5,
    linewidth=2,
    label="moyenne et écart-type test-and-test-and-set",
    color='indigo'
)

plt.errorbar(
    threads,
    meansTAS,
    yerr=stdsTAS,
    fmt='o-',
    capsize=5,
    linewidth=2,
    label="moyenne et écart-type test-and-set",
    color='red'
)

plt.xticks(threads)
plt.grid(True, linestyle="--", alpha=0.5)
plt.legend()

plt.savefig("grapheTAS_TATAS.pdf")
plt.show()
