#!/bin/bash
matrix_sizes=(500 1000 1500)

# Loop over matrix sizes
for N in "${matrix_sizes[@]}"; do
    # Loop over MPI ranks
    for mpi_ranks in 1 2 4; do
        # Loop over number of OpenMP threads
        for omp_threads in 1 2 4; do
            export OMP_NUM_THREADS=$omp_threads
            echo "${mpi_ranks} MPI ranks, ${omp_threads}, ${N}"
            mpiexec -n $mpi_ranks ./Part3 $N >> results.txt
        done
    done
done