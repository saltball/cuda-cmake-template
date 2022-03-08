#ifndef HELLO_HPP
#define HELLO_HPP
#include <cuda_runtime.h>
#include "common.h"
__global__ void hello_world(void)
{
  printf("GPU: Hello world from thread %d of total grid %d, block %d of total blocks %d\n", threadIdx.x, gridDim.x, blockIdx.x, blockDim.x);
}
int hello()
{
  printf("CPU: Hello world!\n");
  initDevice(0);
  double start_t = cpuSecond();
  hello_world<<<10, 10>>>();
  cudaDeviceReset(); // if no this line ,it can not output hello world from gpu
  double end_t = cpuSecond();
  printf("CPU: Time taken: %f\n", end_t - start_t);
  return 0;
}
#endif // HELLO_HPP