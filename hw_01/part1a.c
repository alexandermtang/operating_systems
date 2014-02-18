#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

#include "my_timer.h"

#define B 1
#define KB (1024 * B)
#define MB (1024 * KB)
#define ARR_SIZE (8 * MB)
#define MAX_STRIDE (1024 * B)
#define REPS (32 * 1024 * 1024)
#define SETS 10

// find cache line size
int main(int argc, char** argv)
{
  int lengthMod = ARR_SIZE - 1;
  int i = 0, j = 0, stride = 0, dummy = 0, iter_num = 0;
  int stride_times[(int)log2(MAX_STRIDE)];

  // allocate and initialize arr
  char *arr = malloc(ARR_SIZE);
  for (i = 0; i < ARR_SIZE; i++) { arr[i] = 'a'; }

  for (stride = 1; stride <= MAX_STRIDE; stride *= 2) {
    timer_start();

    for (j = 0; j < SETS; j++) {
      for (i = 0; i < REPS; i++) {
        // use * and modulo to throw off HW prefetching
        dummy = arr[(i * stride) & lengthMod];
      }
    }

    unsigned long long t = timer_stop();
    stride_times[iter_num++] = t; // record time
    printf("stride %d B\ttime %llu usec\n", stride, t);
  }

  // calculate largest difference in times
  for (i = 0; i < iter_num; i++) {
    /*printf("stride %d B\ttime %d usec\n", (int)pow(2, i), stride_times[i]);*/
  }

  free(arr);

  exit(0);
}
