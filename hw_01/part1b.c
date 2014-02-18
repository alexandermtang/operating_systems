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
#define TOTAL_SIZE (8 * MB)
#define NUM_ITERS 100
#define REPS (1024 * 256)

// find cache size
int main(int argc, char** argv)
{
  int i = 0, j = 0, dummy = 0, cache_size_guess = 0;
  unsigned long long times[NUM_ITERS];

  /*for (cache_size_guess = (250 * KB); cache_size_guess < TOTAL_SIZE; cache_size_guess+=KB) {*/
  for (cache_size_guess = LINE_SIZE; cache_size_guess < TOTAL_SIZE; cache_size_guess*=2) {
  /*for (cache_size_guess = 6291136; cache_size_guess < TOTAL_SIZE; cache_size_guess+=LINE_SIZE) {*/
    char *arr = malloc(cache_size_guess);
    for (i = 0; i < cache_size_guess; i++) { arr[i] = 'a'; }

    for (i = 0; i < NUM_ITERS; i++) {

      timer_start();
      for (j = 0; j < REPS; j++) {
        // get random index in arr
        unsigned long rand_index = (rand()*rand()) & (cache_size_guess - 1);
        dummy = arr[rand_index];
      }

      unsigned long long t = timer_stop();
      times[i] = t;
    }
    double time_avg = 0.0;
    for (i = 0; i < NUM_ITERS; i++) { time_avg += times[i]; }
    time_avg /= NUM_ITERS;

    printf("cache_size_guess %d B\ttime %f\n", cache_size_guess, time_avg);
    free(arr);
  }

  exit(0);
}
