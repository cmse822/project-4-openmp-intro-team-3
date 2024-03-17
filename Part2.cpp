/* 

export OMP_NUM_THREADS=4
Compile with mpic++ -fopenmp -o Part2 Part2.cpp 
Execute with mpiexec -n 2 Part2

*/
#include <iostream>
#include "mpi.h"
#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>

using namespace std;


int main(int argc,char *argv[]) {

    int numtasks, rank;

    // Configure MPI Run
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Define OMP parallel block 
    #pragma omp parallel
    {
    int omp_thread = omp_get_thread_num(); //Get with OMP Thread we are on 
    cout << "Hello, World! from omp thread " << omp_thread <<" on MPI rank " << rank << endl;
    }

    MPI_Finalize();

    return 0;
}