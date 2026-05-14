#include<iostream>
#include<cstdlib>

using namespace std;

// Vector Addition function
__global__ void vectorAdd(int *a, int *b, int *result, int n)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;

    if(tid < n)
    {
        result[tid] = a[tid] + b[tid];
    }
}

int main()
{
    int *a, *b, *c;
    int *a_dev, *b_dev, *c_dev;

    int n = 1 << 24;

    a = new int[n];
    b = new int[n];
    c = new int[n];

    int *d = new int[n];

    int size = n * sizeof(int);

    cudaMalloc((void**)&a_dev, size);
    cudaMalloc((void**)&b_dev, size);
    cudaMalloc((void**)&c_dev, size);

    // Array initialization
    for(int i = 0; i < n; i++)
    {
        a[i] = 1;
        b[i] = 2;

        d[i] = a[i] + b[i];   // Calculating Serial addition
    }

    cudaEvent_t start, end;

    cudaEventCreate(&start);
    cudaEventCreate(&end);

    cudaMemcpy(a_dev, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(b_dev, b, size, cudaMemcpyHostToDevice);

    int threads = 1024;
    int blocks = (n + threads - 1) / threads;

    cudaEventRecord(start);

    // Parallel addition program
    vectorAdd<<<blocks, threads>>>(a_dev, b_dev, c_dev, n);

    cudaEventRecord(end);
    cudaEventSynchronize(end);

    float time = 0;

    cudaEventElapsedTime(&time, start, end);

    cudaMemcpy(c, c_dev, size, cudaMemcpyDeviceToHost);

    // Calculate the error term
    int error = 0;

    for(int i = 0; i < n; i++)
    {
        error += d[i] - c[i];

        // cout << "GPU " << c[i] << " CPU " << d[i];
    }

    cout << "Error : " << error;

    cout << "\nTime Elapsed : " << time;

    cudaFree(a_dev);
    cudaFree(b_dev);
    cudaFree(c_dev);

    delete[] a;
    delete[] b;
    delete[] c;
    delete[] d;

    return 0;
}






// How to run :
// 1. Open Google Collab
// 2. New NOtebook and select runtime -> GPU

// 3.  run > %%writefile vector_add.cu
//     then paste the above 94 line code below it.

// 4. after that in next cell 
//       run -> !nvcc vector_add.cu -o vector_add
// 5. run - > !./vector_add

// all set to go.