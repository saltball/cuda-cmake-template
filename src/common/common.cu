#include "common.cpp"
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