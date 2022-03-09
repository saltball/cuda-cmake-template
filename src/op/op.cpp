#include "op.h"
#include <iostream>
#include <fmt/format.h>
// #include <boost/compute.hpp>
void hello_world(void)
{
  std::cout << "CPU kernal: Hello World.\n";
}
int hello()
{
  std::cout << "CPU: Hello world!\n";
  double start_t = cpuSecond();
  hello_world();
  double end_t = cpuSecond();
  std::cout << fmt::format("CPU: Time taken: {}\n", end_t - start_t);
  std::cout << "But I have openmp.\n";
#pragma omp parallel num_threads(2)
  {
    hello_world();
  }
  return 0;
}
