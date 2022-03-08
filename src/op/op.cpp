#include "op.h"
void hello_world(void)
{
  printf("CPU kernal: Hello World.\n");
}
int hello()
{
  printf("CPU: Hello world!\n");
  double start_t = cpuSecond();
  hello_world();
  double end_t = cpuSecond();
  printf("CPU: Time taken: %f\n", end_t - start_t);
  return 0;
}