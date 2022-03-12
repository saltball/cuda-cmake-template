#include "op.h"
#include <cusolverDn.h>

__global__ void op_kernal(double *a, double *b, double *c)
{
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  int j = blockIdx.y * blockDim.y + threadIdx.y;
  int k = blockIdx.z * blockDim.z + threadIdx.z;
  int idx = i + blockDim.x * j + blockDim.x * blockDim.y * k;
  // printf("GPU: threadIdx:(%d,%d,%d) blockIdx:(%d,%d,%d) blockDim:(%d,%d,%d) gridDim(%d,%d,%d)\n. GPU: idx = % d,  a[i] = % d\n",
  //        threadIdx.x, threadIdx.y, threadIdx.z,
  //        blockIdx.x, blockIdx.y, blockIdx.z,
  //        blockDim.x, blockDim.y, blockDim.z,
  //        gridDim.x, gridDim.y, gridDim.z,
  //        idx,
  //        a[idx]);
  c[idx] = a[idx] + b[idx];
}
int op(int dim_x, int dim_y, int dim_z)
{
  std::cout << fmt::format("CPU: Hello world!\n");
  int size_dim = dim_x * dim_y * dim_z;
  std::cout << fmt::format("CPU: size_dim = {}\n", size_dim);
  initDevice(0);

  double *a_h = (double *)malloc(size_dim * sizeof(double));
  double *b_h = (double *)malloc(size_dim * sizeof(double));
  double *c_h = (double *)malloc(size_dim * sizeof(double));
  double *c_from_gpu_h = (double *)malloc(size_dim * sizeof(double));

  memset(c_h, 0, size_dim * sizeof(double));

  double *a_d, *b_d, *c_d;
  CHECK(cudaMalloc((double **)&a_d, size_dim * sizeof(double)));
  CHECK(cudaMalloc((double **)&b_d, size_dim * sizeof(double)));
  CHECK(cudaMalloc((double **)&c_d, size_dim * sizeof(double)));

  initialData(a_h, size_dim);
  initialData(b_h, size_dim);

  CHECK(cudaMemcpy(a_d, a_h, size_dim * sizeof(double), cudaMemcpyHostToDevice));
  CHECK(cudaMemcpy(b_d, b_h, size_dim * sizeof(double), cudaMemcpyHostToDevice));

  dim3 block(dim_x,dim_y*dim_z,1);
  dim3 grid(1, 1, 1);

  double start_t = cpuSecond();
  op_kernal<<<grid, block>>>(a_d, b_d, c_d);
  op_kernal<<<grid, block>>>(b_d, b_d, c_d);
  op_kernal<<<grid, block>>>(a_d, a_d, c_d);

  CHECK(cudaMemcpy(c_from_gpu_h, c_d, size_dim * sizeof(double), cudaMemcpyDeviceToHost));

  cudaDeviceReset(); // if no this line ,it can not output hello world from gpu

  // printVector(c_from_gpu_h, dim);
  double end_t = cpuSecond();
  std::cout << fmt::format("CPU: Time taken: {:.6f}\n", end_t - start_t);
  free(a_h);
  free(b_h);
  free(c_h);
  free(c_from_gpu_h);
  return 0;
}