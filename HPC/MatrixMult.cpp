#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

// Matrix multiplication CUDA
__global__ void matrixMultiplication(int *a, int *b, int *c, int n)
{
    int row = threadIdx.y + blockDim.y * blockIdx.y;
    int col = threadIdx.x + blockDim.x * blockIdx.x;

    int sum = 0;

    if(row < n && col < n)
    {
        for(int j = 0; j < n; j++)
        {
            sum = sum + a[row * n + j] * b[j * n + col];
        }

        c[n * row + col] = sum;
    }
}

int main()
{
    int *a, *b, *c;
    int *a_dev, *b_dev, *c_dev;

    int n = 3;

    a = new int[n * n];
    b = new int[n * n];
    c = new int[n * n];

    int *d = new int[n * n];

    int size = n * n * sizeof(int);

    cudaMalloc((void**)&a_dev, size);
    cudaMalloc((void**)&b_dev, size);
    cudaMalloc((void**)&c_dev, size);

    // Array initialization
    for(int i = 0; i < n * n; i++)
    {
        a[i] = 2;      // rand() % n;
        b[i] = 1;      // rand() % n;

        // d[i] = a[i] + b[i];
    }

    cudaEvent_t start, end;

    cudaEventCreate(&start);
    cudaEventCreate(&end);

    cudaMemcpy(a_dev, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(b_dev, b, size, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(n, n);
    dim3 blocksPerGrid(1, 1);

    if(n * n > 512)
    {
        threadsPerBlock.x = 512;
        threadsPerBlock.y = 512;

        blocksPerGrid.x = ceil((double)n / (double)threadsPerBlock.x);
        blocksPerGrid.y = ceil((double)n / (double)threadsPerBlock.y);
    }

    // GPU Multiplication
    cudaEventRecord(start);

    matrixMultiplication<<<blocksPerGrid, threadsPerBlock>>>(a_dev, b_dev, c_dev, n);

    cudaEventRecord(end);
    cudaEventSynchronize(end);

    float time = 0.0;

    cudaEventElapsedTime(&time, start, end);

    cudaMemcpy(c, c_dev, size, cudaMemcpyDeviceToHost);

    // CPU matrix multiplication
    int sum = 0;

    for(int row = 0; row < n; row++)
    {
        for(int col = 0; col < n; col++)
        {
            sum = 0;

            for(int k = 0; k < n; k++)
            {
                sum = sum + a[row * n + k] * b[k * n + col];
            }

            d[row * n + col] = sum;
        }
    }

    int error = 0;

    for(int i = 0; i < n * n; i++)
    {
        error += d[i] - c[i];

        // cout << " gpu " << c[i] << " CPU " << d[i] << endl;
    }

    cout << "Error : " << error;

    cout << "\nTime Elapsed: " << time;

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