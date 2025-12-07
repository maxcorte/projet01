
from matplotlib import pyplot as plt
import pandas as pd
import numpy as np

path = "projet01/"
files = []
i = 1
for i in range (1, 4):
    filename = "question1" + str(i) + "_performance.csv"
    files.append(filename)

i = 1
for file in files: 
    data = pd.read_csv(file)
    data_mean = data.groupby('thread_total')['total_time_seconds'].mean()
    data_stddev = data.groupby('thread_total')['total_time_seconds'].std(ddof=1)
    title = file.split('/')[-1]
    title_splitted = title.split('_')
    title_graph = ' '.join(title_splitted[0:-1])

    x = data_mean.index
    y = data_mean.values
    yerror = data_stddev.values
    print(y)
    print(yerror)

    plt.figure()
    plt.title(title_graph)
    plt.xlabel('thread numbers')
    plt.ylabel('time in seconds')
    plt.ylim([0, y.max()+y.max()*0.5])
    plt.errorbar(x, y, yerror, marker='o', capsize=4, color='indigo', label="Mean with standard deviation")
    plt.xticks(ticks=x, labels=x)
    plt.legend()
    figure_path = "question1" + str(i) + ".pdf"
    plt.savefig(figure_path)
    i += 1

