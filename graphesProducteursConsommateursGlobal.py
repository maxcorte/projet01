from matplotlib import pyplot as plt
import pandas as pd

csv_file_active = "./part2/producteur/question252.csv"
csv_file_posix = "./part1/producteur/question2.csv"

# Lecture du CSV : chaque ligne = un nombre de threads, les colonnes = runs
data_posix = pd.read_csv(csv_file_posix, skipinitialspace=True)
data_active = pd.read_csv(csv_file_active, skipinitialspace=True)

# Threads correspondant aux lignes : 2, 4, 8, 16, 32
threads = [2, 4, 8, 16, 32]

# Calcul moyenne + écart-type sur les 5 runs pour chaque ligne
means_active = data_active.mean(axis=1)
stds_active = data_active.std(axis=1, ddof=1)

means_posix = data_posix.mean(axis=1)
stds_posix = data_posix.std(axis=1, ddof=1)

# --- Plot ---
plt.figure(figsize=(12, 6))
plt.title("Temps d'exécution en fonction du nombre de threads (moyenne et écart-type)")
plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (secondes)")
plt.ylim(bottom=0)  # axe Y commence à 0 (consigne)
plt.ylim(0, 2)

plt.errorbar(
    threads,
    means_posix,
    yerr=stds_posix,
    fmt='o-',
    capsize=5,
    linewidth=2,
    label="moyenne et écart-type POSIX",
    color='red'
)

plt.errorbar(
    threads,
    means_active,
    yerr=stds_active,
    fmt='o-',
    capsize=5,
    linewidth=2,
    label="moyenne et écart-type attente active",
    color='indigo'
)

plt.xticks(threads)
plt.grid(True, linestyle="--", alpha=0.5)
plt.legend()

plt.savefig("graphe_prod_cons_global.pdf")
plt.show()
