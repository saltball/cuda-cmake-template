#include "op.h"
#include <iostream>
#include <fmt/format.h>
#include <omp.h>
// #include <boost/compute.hpp>
void op_kernal(double *a, double *b, double *c, const int i)
{
  // omp_get_thread_num();
  c[i] = a[i] + b[i];
  // std::cout << fmt::format("CPU kernal: Hello World from Thread {}, from i={}.\n CPU: i={} c[i]={}\n", omp_get_thread_num(), i, i, c[i]);
}
int op(int dim_x, int dim_y, int dim_z)
{
  std::cout << "CPU: Hello world!\n";

#ifndef __CUDACC__
  std::cout << "I don't have cuda support, but I have openmp.\n";
  int size_dim = dim_x * dim_y * dim_z;

  std::cout << fmt::format("CPU: size_dim = {}\n", size_dim);

  double *a = (double *)malloc(size_dim * sizeof(double));
  double *b = (double *)malloc(size_dim * sizeof(double));
  double *c = (double *)malloc(size_dim * sizeof(double));

  initialData(a, size_dim);
  initialData(b, size_dim);
  int i, j, k;

  double start_t = cpuSecond();
#pragma omp parallel for
  for (i = 0; i < dim_x; i++)
  {
    #pragma omp parallel for
    for (j = 0; j < dim_y; j++)
    {
      #pragma omp parallel for
      for (k = 0; k < dim_z; k++)
      {
        op_kernal(a, b, c, i*dim_y*dim_z+j*dim_z+k);
      }
    }
  }
#pragma omp parallel for
  for (i = 0; i < dim_x; i++)
  {
    #pragma omp parallel for
    for (j = 0; j < dim_y; j++)
    {
      #pragma omp parallel for
      for (k = 0; k < dim_z; k++)
      {
        op_kernal(b, b, c, i*dim_y*dim_z+j*dim_z+k);
      }
    }
  }
#pragma omp parallel for
  for (i = 0; i < dim_x; i++)
  {
    #pragma omp parallel for
    for (j = 0; j < dim_y; j++)
    {
      #pragma omp parallel for
      for (k = 0; k < dim_z; k++)
      {
        op_kernal(a, a, c, i*dim_y*dim_z+j*dim_z+k);
      }
    }
  }

#endif
  double end_t = cpuSecond();
  std::cout << fmt::format("CPU: Time taken: {:.6f}\n", end_t - start_t);
  free(a);
  free(b);
  free(c);
  return 0;
}
