#include <iostream>
#include <vector>
#include "get_walltime.c"
#include <omp.h>

using namespace std;

// Define Matrix data type
typedef vector<vector<double>> Matrix;

// Function to generate a random N x N matrix
Matrix generateRandomMatrix(int N) {
    // Create matrix object 
    Matrix matrix(N, vector<double>(N));

    // Populate matrix object 
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // Assigning random number between 0-9
            matrix[i][j] = rand() % 10;   
        }
    }

    // Confirm matrix has been generated
    cout << "Randomly generated " << N << "x" << N << " matrix" << endl;

    // Return matrix object
    return matrix;
}

// Function to multiply matrices together with OpenMP parallelization
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    Matrix result(rowsA, vector<double>(colsB));

    // Parallelize the matrix multiplication loop
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

// Function to multiply matrices together without OpenMP parallelization
Matrix multiplyMatrices_serial(const Matrix& A, const Matrix& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    Matrix result(rowsA, vector<double>(colsB));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}


// Function to print the matrix (if you so choose)
void printMatrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            cout << val << "\t";
        }
        cout << endl << endl;
    }
}

// Main function 
int main(int argc, char *argv[]) {
    // Must feed in matrix size on the command line 
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <MatrixSize>" << endl;
        return 1;
    }

    // Pull Matrix Size from command line 
    int N = atoi(argv[1]);

    // Must feed in a positive integer for the size of the matrix   
    if (N <= 0) {
        cerr << "Matrix size must be a positive integer." << endl;
        return 1;
    }

    // Randomly populate Matrices A and B 
    Matrix matrixA = generateRandomMatrix(N);
    Matrix matrixB = generateRandomMatrix(N);

    // Define start and end time to calculate the time taken for multiplication. 
    double startTime, endTime;
 
    // Multiply Matrices together 
    get_walltime(&startTime);
    Matrix product1 = multiplyMatrices(matrixA, matrixB);
    get_walltime(&endTime);

    // Calculate elapsed time 
    double elapsedTime = endTime - startTime;

    // Output Results to the terminal 
    cout << "Time elapsed parallel: " << elapsedTime << " seconds." << endl;
    
    // Multiply Matrices together 
    get_walltime(&startTime);
    Matrix product2 = multiplyMatrices_serial(matrixA, matrixB);
    get_walltime(&endTime);

    // Calculate elapsed time 
    elapsedTime = endTime - startTime;

    // Output Results to the terminal 
    cout << "Time elapsed: " << elapsedTime << " seconds." << endl;

    // Optional: Print matrices and see final multiplication result 
    /*
    cout << "MATRIX A:" << endl;
    printMatrix(matrixA);

    cout << "MATRIX B:" << endl;
    printMatrix(matrixB);

    cout << "MATRIX C (The matrix product of A and B):" << endl;
    printMatrix(product);
    */

    return 0;
}
