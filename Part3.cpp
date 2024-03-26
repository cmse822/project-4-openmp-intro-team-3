#include <iostream>
#include <vector>
#include <cstdlib>
#include <mpi.h>
#include <omp.h>
#include <fstream>

using namespace std;

typedef vector<vector<double>> Matrix;

// Simplified function signatures
Matrix generateRandomMatrix(int N);
void printMatrix(const Matrix& matrix);
void writeMatrixToFile(const Matrix& matrix, const string& filename);

// Function to generate a random matrix of size NxN
Matrix generateRandomMatrix(int N) {
    Matrix matrix(N, vector<double>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10; // Random number between 0 and 9
        }
    }
    return matrix;
}

// Function to print the matrix - for verification
void printMatrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << "\n";
    }
}

void writeMatrixToFile(const Matrix& matrix, const string& filename) {
    ofstream file(filename);
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            file << elem << " ";
        }
        file << "\n";
    }
    file.close();
}


int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int mpi_size, mpi_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

    // Define the size of the matrix
    int N = 1000;
    if(argc == 2) {
        N = atoi(argv[1]);
    }

    vector<double> A_flat(N * N), B_flat(N * N), C_flat(N * N, 0), local_A_flat(N * N / mpi_size), local_C_flat(N * N / mpi_size, 0);
    Matrix A, B, C;

    if (mpi_rank == 0) {
        A = generateRandomMatrix(N);
        B = generateRandomMatrix(N);
        // Flatten matrices A and B for MPI
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                A_flat[i * N + j] = A[i][j];
                B_flat[i * N + j] = B[i][j];
            }
        }
    }

    // Broadcast the entire matrix B to all processes
    MPI_Bcast(&B_flat[0], N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Scatter the rows of matrix A across all processes
    MPI_Scatter(&A_flat[0], N*N/mpi_size, MPI_DOUBLE, &local_A_flat[0], N*N/mpi_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double start_time, end_time, local_elapsed, elapsed;

    MPI_Barrier(MPI_COMM_WORLD); // Ensure all processes start timing at the same point
    start_time = MPI_Wtime();

    // Each process computes its part of the matrix multiplication
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N / mpi_size; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                local_C_flat[i * N + j] += local_A_flat[i * N + k] * B_flat[k * N + j];
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD); // Ensure all processes finish before stopping the timer
    end_time = MPI_Wtime();
    local_elapsed = end_time - start_time;

    // Gather the computed parts back to the root process
    MPI_Gather(&local_C_flat[0], N*N/mpi_size, MPI_DOUBLE, &C_flat[0], N*N/mpi_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    // Find the maximum time across all processes
    MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (mpi_rank == 0) {
        // Reconstruct the result matrix C from the flat array
        C.resize(N, vector<double>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                C[i][j] = C_flat[i * N + j];
            }
        }
        // print matrix C to verify the results
        //printMatrix(C);

        //writeMatrixToFile(A,"Part3_1_matrixA.txt");
        //writeMatrixToFile(B,"Part3_1_matrixB.txt");
        //writeMatrixToFile(C,"Part3_1_matrixC.txt");
        //cout << "Elapsed time: " << elapsed << " seconds." << endl;
       cout << elapsed << endl; 
    }

    MPI_Finalize();
    return 0;
}