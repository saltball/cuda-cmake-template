#include "common.h"
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#ifdef _WIN32
int gettimeofday(struct timeval *tp, void *tzp)
{
  time_t clock;
  struct tm tm;
  SYSTEMTIME wtm;
  GetLocalTime(&wtm);
  tm.tm_year = wtm.wYear - 1900;
  tm.tm_mon = wtm.wMonth - 1;
  tm.tm_mday = wtm.wDay;
  tm.tm_hour = wtm.wHour;
  tm.tm_min = wtm.wMinute;
  tm.tm_sec = wtm.wSecond;
  tm.tm_isdst = -1;
  clock = mktime(&tm);
  tp->tv_sec = clock;
  tp->tv_usec = wtm.wMilliseconds * 1000;
  return (0);
}
#endif
double cpuSecond()
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return ((double)tp.tv_sec + (double)tp.tv_usec * 1e-6);
}
void initialData(float *ip, int size)
{
  time_t t;
  srand((unsigned)time(&t));
  for (int i = 0; i < size; i++)
  {
    ip[i] = (float)(rand() & 0xffff) / 1000.0f;
  }
}
void initialData_int(int *ip, int size)
{
  time_t t;
  srand((unsigned)time(&t));
  for (int i = 0; i < size; i++)
  {
    ip[i] = int(rand() & 0xff);
  }
}
void printMatrix(float *C, const int nx, const int ny)
{
  float *ic = C;
  std::cout<<fmt::format("Matrix<{},{}>:", ny, nx);
  for (int i = 0; i < ny; i++)
  {
    for (int j = 0; j < nx; j++)
    {
      std::cout<<fmt::format("{:6f} ", C[j]);
    }
    ic += nx;
    std::cout<<fmt::format("\n");
  }
}
#ifdef __CUDACC__
void initDevice(int devNum)
{
  int dev = devNum;
  cudaDeviceProp deviceProp;
  CHECK(cudaGetDeviceProperties(&deviceProp, dev));
  std::cout<<fmt::format("Using device {}: {}\n", dev, deviceProp.name);
  CHECK(cudaSetDevice(dev));
}
void checkResult(float *hostRef, float *gpuRef, const int N)
{
  double epsilon = 1.0E-8;
  for (int i = 0; i < N; i++)
  {
    if (fabs(hostRef[i] - gpuRef[i]) > epsilon)
    {
      std::cout<<fmt::format("Results don\'t match!\n");
      std::cout<<fmt::format("{}(hostRef[{}] )!= {}(gpuRef[{}])\n", hostRef[i], i, gpuRef[i], i);
      return;
    }
  }
  std::cout<<fmt::format("Check result success!\n");
}
#endif