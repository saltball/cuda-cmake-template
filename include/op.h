#ifndef HELLO_HPP
#define HELLO_HPP
#include "common.h"
#include <vector>
#ifdef __CUDACC__
#include <cuda_runtime.h>
__global__ void op_kernal(long *a, long *b, long *c);
#else
void op_kernal(long *a, long *b, long *c, const int i);
#endif
int op(int dim_x, int dim_y, int dim_z);
#endif // HELLO_HPP
