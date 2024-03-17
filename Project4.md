# Project 4

## Part 1: OpenMP Matrix-Matrix Multiplication

### 1.1 Solution 

See code `Part1.cpp`.

### 1.2 Solution

## Part 2: Adding OpenMP threading to a simple MPI Application 

### 2.1 to 2.4 Solution 

See code `Part2.cpp`.

### 2.5 Solution

I modified the "Hello World!" output slightly so that I could more accurately determine what was going on. We can see the rsults of running `Part2.cpp` below:
   
    Hello, World! from omp thread 1 on MPI rank 0
    Hello, World! from omp thread 0 on MPI rank 0
    Hello, World! from omp thread 2 on MPI rank 0
    Hello, World! from omp thread 3 on MPI rank 0
    Hello, World! from omp thread 1 on MPI rank 1
    Hello, World! from omp thread 0 on MPI rank 1
    Hello, World! from omp thread 2 on MPI rank 1
    Hello, World! from omp thread 3 on MPI rank 1

We can see that each rank of MPI compiles the entire code and runs it (as expected). Within each MPI rank it encounters the OMP parallelized block, which we have assigned to 4 threads. It runs each of these 4 threads which return in a random order each time (as expected again) each thread with its own individual "Hello World!". This gives us a total of 8 "Hello World!"s coming from 4 threads*2ranks. 