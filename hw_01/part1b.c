#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

#include "my_timer.h"

#define B 1
#define KB (1024 * B)
#define MB (1024 * KB)
#define LINE_SIZE (64 * B)  // determined using ./part1a
#define TOTAL_SIZE (64 * MB)
#define MAX_LINES 32768     // guess that cache has between [1, MAX_LINES] lines
#define REPS (32 * 1024)
#define SETS 5

// find cache size
int main(int argc, char** argv)
{
  int i = 0, j = 0, num_lines = 0, dummy = 0; //, iter_num = 0;
  /*int stride_times[(int)log2(MAX_STRIDE)];*/

  // allocate and initialize arr
  char *arr = malloc(TOTAL_SIZE);
  for (i = 0; i < TOTAL_SIZE; i++) { arr[i] = 'a'; }

  for (num_lines = 1; num_lines <= MAX_LINES; num_lines *= 2) {
    unsigned long arr_size = LINE_SIZE * num_lines;
    int lengthMod = arr_size - 1;

    timer_start();

    for (j = 0; j < SETS; j++) {
      for (i = 0; i < REPS; i++) {
        // use * and modulo to throw off HW prefetching
        dummy += arr[(i * LINE_SIZE) & lengthMod];
      }
    }

    unsigned long long t = timer_stop();
    printf("# lines %d\tblock size %d B\ttime %llu usec\n",
        num_lines, num_lines * LINE_SIZE, t);
  }

  free(arr);
  exit(0);
}
