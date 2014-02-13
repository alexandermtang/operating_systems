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
#define REPS ARR_SIZE
#define SETS 20

void find_cache_line_size(void)
{
  char *arr = malloc(ARR_SIZE);
  int lengthMod = ARR_SIZE - 1;
  int i = 0, j = 0, stride = 0, dummy = 0, iter_num = 0;
  int stride_times[(int)log2(MAX_STRIDE)];

  // initialize arr
  for (i = 0; i < ARR_SIZE; i++) { arr[i] = 'a'; }

  for (stride = 1; stride <= MAX_STRIDE; stride *= 2) {
    timer_start();

    for (j = 0; j < SETS; j++) {
      for (i = 0; i < REPS; i++) {
        // use * and modulo to throw off HW prefetching
        dummy = arr[(i * stride) & lengthMod];
      }
    }

    stride_times[iter_num++] = timer_stop(); // record time
  }

  for (i = 0; i < iter_num; i++) {
    printf("stride %d B\ttime %d usec\n", (int)pow(2, i), stride_times[i]);
  }

  free(arr);
}

int main(int argc, char** argv)
{
  find_cache_line_size();

  exit(0);
}
