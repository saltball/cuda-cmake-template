/*
*hello_world.cu
*/
#include<stdio.h>
__global__ void hello_world(void)
{
  printf("GPU: Hello world from thread %d of total grid %d, block %d of total blocks %d\n", threadIdx.x, gridDim.x, blockIdx.x, blockDim.x);
}
int main(int argc,char **argv)
{
  printf("CPU: Hello world!\n");
  hello_world<<<2,10>>>();
  cudaDeviceReset();//if no this line ,it can not output hello world from gpu
  return 0;
}