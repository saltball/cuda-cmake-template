#ifndef HELLO_HPP
#define HELLO_HPP
#include <cuda_runtime.h>
#include "common.h"
__global__ void hello_world(void);
int hello();
#endif // HELLO_HPP