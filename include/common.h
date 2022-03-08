#ifndef QC_COMMON_HPP
#define QC_COMMON_HPP

#include <stdio.h>
#include <math.h>

#define CHECK(call)                                                    \
  {                                                                    \
    const cudaError_t error = call;                                    \
    if (error != cudaSuccess)                                          \
    {                                                                  \
      printf("ERROR: %s:%d,", __FILE__, __LINE__);                     \
      printf("code:%d,reason:%s\n", error, cudaGetErrorString(error)); \
      exit(1);                                                         \
    }                                                                  \
  }

#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#ifdef _WIN32
int gettimeofday(struct timeval *tp, void *tzp);
#endif
double cpuSecond();
void initialData(float *ip, int size);
void initialData_int(int *ip, int size);
void printMatrix(float *C, const int nx, const int ny);
#ifdef __CUDACC__
void initDevice(int devNum);
void checkResult(float *hostRef, float *gpuRef, const int N);
#endif
#endif // QC_COMMON_HPP