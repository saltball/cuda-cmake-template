#ifndef HELLO_HPP
#define HELLO_HPP
#include "common.h"
#ifdef __CUDACC__
#include <cuda_runtime.h>
__global__
#endif
    void
    hello_world(void);
int hello();
#endif // HELLO_HPP