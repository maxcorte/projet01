from matplotlib import pyplot as plt
import pandas as pd
import numpy as np


files = ["projet01/lecteurs_ecrivains_performance.csv", "projet01/philosophes_performance.csv", "projet01/producteurs_consommateurs_performance.csv"]

for file in files: 
    data = pd.read_csv(file)
    data_mean = data.groupby('thread_total').mean()
    data_stddev = data.groupby('thread_total').agg(np.std, ddof=1)
    print(data_mean)
    print(data_stddev)

    title = str(file[9:-4])
    title_splitted = title.split('_')
    title_graph = ' '.join(title_splitted[0:-1])
    plt.figure()
    plt.title(title_graph)
    plt.xlabel('thread numbers')
    plt.ylabel('time in seconds')
    plt.plot(data_mean['total_time_seconds'], marker='o')
    plt.xticks(ticks=data_mean.index, labels=data_mean.index)
    plt.savefig(title)

