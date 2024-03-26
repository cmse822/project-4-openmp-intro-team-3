#!/bin/bash

#number of OpenMP threads to use
export OMP_NUM_THREADS=4

#Compile
mpic++ -fopenmp -o Part3 Part3.cpp

#Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
else
    echo "Compilation failed."
    exit 1
fi


# Run the program with 2 MPI processes (adjust as necessary for your system)
mpiexec -n 2 ./Part3

#rm Part3
