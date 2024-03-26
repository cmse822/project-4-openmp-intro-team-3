import matplotlib.pyplot as plt
import pandas as pd


data = pd.read_csv('results.txt', delimiter=' ', header=1, names=['Time','MPI_Ranks', 'OMP_Threads', 'Matrix_Size'])
data



filtered_data = data[data['Matrix_Size'] == 1000]
matrix_size = 1000


colors = {1: 'red', 2: 'blue', 4: 'green'}

# Plotting
for omp_threads, color in colors.items():
    subset = filtered_data[filtered_data['OMP_Threads'] == omp_threads]
    plt.plot(subset['MPI_Ranks'], subset['Time'], label=f'OMP Threads={omp_threads}', color=color)

plt.xlabel('MPI Ranks')
plt.ylabel('Execution Time (s)')
plt.title(f'Performance for Matrix Size {matrix_size}')
plt.legend()
plt.grid(True)
plt.show()


filtered_data = data[data['Matrix_Size'] == 500]
matrix_size = 500


colors = {1: 'red', 2: 'blue', 4: 'green'}

# Plotting
for omp_threads, color in colors.items():
    subset = filtered_data[filtered_data['OMP_Threads'] == omp_threads]
    plt.plot(subset['MPI_Ranks'], subset['Time'], label=f'OMP Threads={omp_threads}', color=color)

plt.xlabel('MPI Ranks')
plt.ylabel('Execution Time (s)')
plt.title(f'Performance for Matrix Size {matrix_size}')
plt.legend()
plt.grid(True)
plt.show()

filtered_data = data[data['Matrix_Size'] == 1500]
matrix_size = 1500


colors = {1: 'red', 2: 'blue', 4: 'green'}


for omp_threads, color in colors.items():
    subset = filtered_data[filtered_data['OMP_Threads'] == omp_threads]
    plt.plot(subset['MPI_Ranks'], subset['Time'], label=f'OMP Threads={omp_threads}', color=color)

plt.xlabel('MPI Ranks')
plt.ylabel('Execution Time (s)')
plt.title(f'Performance for Matrix Size {matrix_size}')
plt.legend()
plt.grid(True)
plt.show()