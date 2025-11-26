
from matplotlib import pyplot as plt
import pandas as pd
import numpy as np


###########################################################
### Partie pour plot le graphe des questions 2.2 et 2.3 ###
###########################################################

question2_data = pd.read_csv("question22_performance.csv")
question2_mean = question2_data.groupby('thread_total')['total_time_seconds'].mean()
question2_stddev = question2_data.groupby('thread_total')['total_time_seconds'].std(ddof=1)

question3_data = pd.read_csv("question23_performance.csv")
question3_mean = question3_data.groupby('thread_total')['total_time_seconds'].mean()
question3_stddev = question3_data.groupby('thread_total')['total_time_seconds'].std(ddof=1)

title = "Performance verrou test-and-set et test-and-test-and-set"


x = question2_mean.index

y2 = question2_mean.values
yerror2 = question2_stddev.values

y3 = question3_mean.values
yerror3 = question3_stddev.values

max_y = np.max(y2, y3)

plt.figure()
plt.title(title)
plt.xlabel('Nombre de threads')
plt.ylabel('Temps en secondes')
plt.ylim([0, max_y+max_y*0,5])
plt.errorbar(x, y2, yerror2, marker='o', capsize=4, color='indigo', label="Algorithme test-and-set")
plt.errorbar(x, y3, yerror3, marker='o', capsize=4, color='blue', label="Algorithme test-and-test-and-set")
plt.xticks(ticks=x, labels=x)
plt.legend()
figure_path = "PlotQuestion_22_23.pdf"
plt.savefig(figure_path)

###########################################################################################
### Partie pour plot les graphes de comparaison des deux attentes (actives et passives) ###
###########################################################################################

files_active_wait = []
files_passive_wait = []
i = 1
for i in range (1, 4):
    filenames_active_wait = "question251" + str(i) + "_performance.csv"
    files_active_wait.append(filenames_active_wait)
    filenames_passive_wait = "question1" + str(i) + "_performance.csv"
    files_passive_wait.append(filenames_passive_wait)
    

i = 1
for i in range(0, len(files_active_wait)): 
    # Récupération des 2 bases de données
    active_wait_filename = files_active_wait[i]
    active_wait_data = pd.read_csv(active_wait_filename)
    active_wait_data_mean = active_wait_data.groupby('thread_total')['total_time_seconds'].mean()
    active_wait_data_stddev = active_wait_data.groupby('thread_total')['total_time_seconds'].std(ddof=1)

    passive_wait_file = files_passive_wait[i]
    passive_wait_data = pd.read_csv(passive_wait_file)
    passive_wait_data_mean = passive_wait_data.groupby('thread_total')['total_time_seconds'].mean()
    passive_wait_data_stddev = passive_wait_data.groupby('thread_total')['total_time_seconds'].std(ddof=1)

    # Titre du graphe
    title = active_wait_filename.split('/')[-1]
    title_splitted = title.split('_')
    title_graph = title_splitted[0]
    match title_graph:
        case "question2511":
            title_graph = "Problème des philosophes"
        case "question2511":
            title_graph = "Problème des producteurs et consommateurs"
        case "question2513":
            title_graph = "Problème des lecteurs et écrivains"
    
    # Plot
    x = active_wait_data_mean.index

    active_y = active_wait_data_mean.values
    active_yerror = active_wait_data_stddev.values

    passive_y = passive_wait_data_mean.values
    passive_yerror = passive_wait_data_stddev.values

    max_y = np.max(passive_y, active_y)


    plt.figure()
    plt.title(title_graph)
    plt.xlabel('thread numbers')
    plt.ylabel('time in seconds')
    plt.ylim([0, max_y+max_y*0,5])
    plt.errorbar(x, active_y, active_yerror, marker='o', capsize=4, color='indigo', label="Moyenne avec attente active")
    plt.errorbar(x, passive_y, passive_yerror, marker='o', capsize=4, color='blue', label="Moyenne avec attente passive")
    plt.xticks(ticks=x, labels=x)
    plt.legend()
    figure_path = "GlobalPlotQuestion" + str(i) + ".pdf"
    plt.savefig(figure_path)
    i += 1

