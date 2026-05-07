#include <iostream>
#include <cuda_runtime.h>

using namespace std;

// ---------------- VECTOR ADDITION KERNEL ----------------
__global__ void vectorAdd(int *A, int *B, int *C, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
    {
        C[i] = A[i] + B[i];
    }
}

// ---------------- MATRIX MULTIPLICATION KERNEL ----------------
__global__ void matrixMul(int *A, int *B, int *C, int n)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n)
    {
        int sum = 0;

        for (int k = 0; k < n; k++)
        {
            sum += A[row * n + k] * B[k * n + col];
        }

        C[row * n + col] = sum;
    }
}

int main()
{
    // -------- VECTOR ADDITION -------
    int n = 5;
    int size = n * sizeof(int);

    int h_A[] = {1, 2, 3, 4, 5};
    int h_B[] = {5, 4, 3, 2, 1};
    int h_C[5];

    int *d_A, *d_B, *d_C;

    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    vectorAdd<<<1, n>>>(d_A, d_B, d_C, n);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    cout << "Vector Addition Result:\n";

    for (int i = 0; i < n; i++)
    {
        cout << h_C[i] << " ";
    }

    cout << endl;

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    // -------- MATRIX MULTIPLICATION -------
    int N = 2;
    int bytes = N * N * sizeof(int);

    int h_M1[] = {1, 2, 3, 4};
    int h_M2[] = {5, 6, 7, 8};
    int h_M3[4];

    int *d_M1, *d_M2, *d_M3;

    cudaMalloc(&d_M1, bytes);
    cudaMalloc(&d_M2, bytes);
    cudaMalloc(&d_M3, bytes);

    cudaMemcpy(d_M1, h_M1, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_M2, h_M2, bytes, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(2, 2);
    dim3 blocksPerGrid(1, 1);

    matrixMul<<<blocksPerGrid, threadsPerBlock>>>(d_M1, d_M2, d_M3, N);

    cudaMemcpy(h_M3, d_M3, bytes, cudaMemcpyDeviceToHost);

    cout << "\nMatrix Multiplication Result:\n";

    for (int i = 0; i < N * N; i++)
    {
        cout << h_M3[i] << " ";
    }

    cout << endl;

    cudaFree(d_M1);
    cudaFree(d_M2);
    cudaFree(d_M3);

    return 0;
}