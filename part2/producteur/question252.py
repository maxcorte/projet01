from matplotlib import pyplot as plt
import pandas as pd

csv_file = "./question252.csv"

# Lecture du CSV : chaque ligne = un nombre de threads, les colonnes = runs
data = pd.read_csv(csv_file, skipinitialspace=True)

# Threads correspondant aux lignes : 2, 4, 8, 16, 32
threads = [2, 4, 8, 16, 32]

# Calcul moyenne + écart-type sur les 5 runs pour chaque ligne
means = data.mean(axis=1)
stds = data.std(axis=1, ddof=1)

# --- Plot ---
plt.figure(figsize=(12, 6))
plt.title("Temps d'exécution en fonction du nombre de threads (moyenne et écart-type)")
plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (secondes)")
plt.ylim(bottom=0)  # axe Y commence à 0 (consigne)
plt.ylim(0, 2)


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

plt.savefig("plot_question2_attente_active.pdf")
plt.show()
