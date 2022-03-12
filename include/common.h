#ifndef QC_COMMON_HPP
#define QC_COMMON_HPP

#include <iostream>
#include <fmt/format.h>
#include <math.h>

#define CHECK(call)                                                                      \
  {                                                                                      \
    const cudaError_t error = call;                                                      \
    if (error != cudaSuccess)                                                            \
    {                                                                                    \
      std::cout << fmt::format("ERROR: {}:{},", __FILE__, __LINE__);                     \
      std::cout << fmt::format("code:{},reason:{}\n", error, cudaGetErrorString(error)); \
      exit(1);                                                                           \
    }                                                                                    \
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
void initialData(int *ip, int size);
void initialData(long *ip, int size);
void initialData(long long *ip, int size);
void initialData(double *ip, int size);
void initialMatrix(long long *ip, int size_dim1, int size_dim2);
void initialMatrix(long long *ip, int size_dim1, int size_dim2, int size_dim3);
template <class T>
void printVector(T *C, const int n)
{
  for (int i = 0; i < n; i++)
  {
    std::cout << C[i] << " ";
  }
  std::cout << "\n";
}
template <class T>
void printMatrix(T *C, const int nx, const int ny)
{
  T *ic = C;
  std::cout << fmt::format("Matrix<{:d},{:d}>:", ny, nx);
  for (int i = 0; i < ny; i++)
  {
    for (int j = 0; j < nx; j++)
    {
      std::cout << fmt::format("{:6f} ", C[j]);
    }
    ic += nx;
    std::cout << fmt::format("\n");
  }
};
#ifdef __CUDACC__
void initDevice(int devNum);
void checkResult(float *hostRef, float *gpuRef, const int N);
#endif
#endif // QC_COMMON_HPP
