#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

#include "my_timer.h"

#define B 1
#define KB (1024 * B)
#define MB (1024 * KB)
#define LINE_SIZE (64 * B)    // determined from ./part1a
#define CACHE_SIZE (256 * KB) // determined from ./part1b
#define NUM_ITERS 10000

// find cache miss penalty
int main(int argc, char** argv)
{
  int i = 0, dummy = 0;
  unsigned long long times[NUM_ITERS];

  char *cache = malloc(CACHE_SIZE);
  for (i = 0; i < CACHE_SIZE; i++) { cache[i] = 'a'; }

  for (i = 0; i < NUM_ITERS; i++) {
    unsigned long rand_index = (rand()*rand()) & (CACHE_SIZE - 1);
    timer_start();
    dummy = cache[rand_index];
    unsigned long long t = timer_stop();
    times[i] = t;
  }
  double time_avg = 0.0;
  for (i = 0; i < NUM_ITERS; i++) { time_avg += times[i]; }
  time_avg /= NUM_ITERS;
  printf("cache size %d B\ttime %f usec\n", CACHE_SIZE, time_avg);
  free(cache);

  int BIGGER_THAN_CACHE_SIZE = CACHE_SIZE * 2;
  char *bigger_than_cache = malloc(BIGGER_THAN_CACHE_SIZE);
  for (i = 0; i < BIGGER_THAN_CACHE_SIZE; i++) { bigger_than_cache[i] = 'a'; }

  for (i = 0; i < NUM_ITERS; i++) {
    unsigned long rand_index = (rand()*rand()) & (BIGGER_THAN_CACHE_SIZE - 1);
    timer_start();
    dummy = bigger_than_cache[rand_index];
    unsigned long long t = timer_stop();
    times[i] = t;
  }
  time_avg = 0.0;
  for (i = 0; i < NUM_ITERS; i++) { time_avg += times[i]; }
  time_avg /= NUM_ITERS;
  printf("cache size %d B\ttime %f usec\n", BIGGER_THAN_CACHE_SIZE, time_avg);
  free(bigger_than_cache);

  exit(0);
}
