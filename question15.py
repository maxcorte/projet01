from matplotlib import pyplot as plt
import pandas as pd
import numpy as np

path = "./"
files = []
i = 1

for i in range (1, 4):
    filename = path + "question1" + str(i) + "_performance.csv"
    files.append(filename)

i = 1
for file in files: 
    data = pd.read_csv(file)
    data_mean = data.groupby('thread_total').mean()
    data_stddev = data.groupby('thread_total').agg(np.std, ddof=1)
    title = file.split('/')[-1]
    title_splitted = title.split('_')
    title_graph = ' '.join(title_splitted[0:-1])
    plt.figure()
    plt.title(title_graph)
    plt.xlabel('thread numbers')
    plt.ylabel('time in seconds')
    plt.ylim([0, data_mean['total_time_seconds'].max()+data_mean['total_time_seconds'].max()*0.1])
    plt.plot(data_mean['total_time_seconds'], marker='o', color='indigo')
    plt.plot(data_stddev['total_time_seconds'], marker='x', color='deepskyblue')
    plt.xticks(ticks=data_mean.index, labels=data_mean.index)
    figure_path = path + "question1" + str(i) + ".pdf"
    plt.savefig(figure_path)
    i += 1

