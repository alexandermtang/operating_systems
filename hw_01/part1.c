#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "my_timer.h"

#define KB 1024
#define MB (1024 * KB)
#define ARR_SIZE (8 * MB)
#define MAX_STRIDE 512

int main(int argc, char** argv)
{
  int num_ints = ARR_SIZE / sizeof(int);
  int *arr = malloc(ARR_SIZE / sizeof(int));
  int lengthMod = ARR_SIZE / sizeof(int) - 1;
  int i = 0, j = 0, stride = 0, dummy = 0;

  // map array to physical memory
  for (i = 0; i < num_ints; i++) { arr[i] = 128; }

  for (stride = 4; stride <= MAX_STRIDE; stride *= 2) {
    timer_start();
    dummy = 0;
    for (j = 0; j < 10; j++) {
      for (i = 0; i < ARR_SIZE; i += stride) {
        dummy += arr[(i * stride) % lengthMod];
      }
    }
    printf("stride %d\t%d B\ttime ", stride, stride * 4);
    timer_stop();
  }

  free(arr);

  exit(0);
}
