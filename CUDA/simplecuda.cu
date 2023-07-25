#include <iostream>
#include <math.h>

__global__
void add(int n, float *x, float *y)
{
    for (int i; i<n; i++)
        y[i] = x[i] + y[i];
}

int main(void)
{
    int N = 1<<20; // 1M elements

    float *x, *y;
    cudaMallocManaged(&x, N*sizeof(float));
    cudaMallocManaged(&y, N*sizeof(float));

    for (int i = 0; i < N; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    // run kernel
    // add(N, x, y);
    add<<<1,1>>>(N, x, y);
    cudaDeviceSynchronize();

    float maxError = 0.0f;
    for(int i = 0; i < N; i++)
        maxError = fmax(maxError, fabs(y[i]-3.0f));
    
    std::cout << "Max error: " << maxError << std::endl;

    // free memory
    cudaFree(x);
    cudaFree(y);

    return 0;
}