#include <chrono>     // Include the chrono library for timing
#include <cstdlib>    // Include the cstdlib library for rand() and srand()
#include <iostream>   // Include the iostream library for input/output
#include <thread>     // Include the std::thread library for parallel execution
#include <vector>     // Include the vector library for dynamic arrays
#include <time.h>     // Include the time.h library for time()

using namespace std::chrono;  // Use the std::chrono namespace for time-related functions
using namespace std;          // Use the standard namespace for standard library functions

// Function to generate random integers and fill an array
void randomVector(int vector[], int size) {
  for (int i = 0; i < size; i++) {
    vector[i] = rand() % 100;  // Assign a random number between 0 and 99 to each element
  }
}

// Function to add corresponding elements of two arrays in parallel
void addArrays(int v1[], int v2[], int v3[], int start, int end) {
  for (int i = start; i < end; i++) {
    v3[i] = v1[i] + v2[i];
  }
}

int main() {
  unsigned long size = 100000000;  // Size of the arrays
  srand(time(0));  // Seed the random number generator with the current time
  
  // Declare pointers for three arrays
  int *v1, *v2, *v3;

  // Dynamically allocate memory for the arrays
  v1 = (int *)malloc(size * sizeof(int));
  v2 = (int *)malloc(size * sizeof(int));
  v3 = (int *)malloc(size * sizeof(int));
// Generate random numbers and fill the arrays
  randomVector(v1, size);
  randomVector(v2, size);

  auto start = high_resolution_clock::now();  // Record the starting time
  
  // Define the number of threads to use (assuming 4 threads here)
  int numThreads = 4;
  int chunkSize = size / numThreads;

  // Create a vector to hold thread objects
  vector<thread> threads;

  // Create and start threads for parallel addition
  for (int i = 0; i < numThreads; i++) {
    threads.push_back(thread(addArrays, v1, v2, v3, i * chunkSize, (i + 1) * chunkSize));
  }

  // Wait for all threads to finish
  for (int i = 0; i < numThreads; i++) {
    threads[i].join();
  }
  
  auto stop = high_resolution_clock::now();  // Record the stopping time
  auto duration = duration_cast<microseconds>(stop - start);  // Calculate the elapsed time
  
  // Output the elapsed time
  cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
  
  // Free dynamically allocated memory
  free(v1);
  free(v2);
  free(v3);
  
  return 0;
}
