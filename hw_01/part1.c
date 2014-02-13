#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "my_timer.h"

#define ARR_SIZE (1024 * 1024)
#define NUM_TIMES 1000

int main(int argc, char** argv)
{
  int arr[ARR_SIZE], dummy;
  int i = 0, j = 0;

  // map array to physical memory
  for (i = 0; i < ARR_SIZE; i++) { arr[i] = rand() % INT_MAX; }

  timer_start();
  for (j = 0; j < 1000; j++) {
    for (i = 0; i < ARR_SIZE; i++) { dummy = arr[i]; }
  }
  timer_stop();

  timer_start();
  for (j = 0; j < 1000; j++) {
    for (i = 0; i < ARR_SIZE; i+=2) { dummy = arr[i]; }
  }
  timer_stop();

  timer_start();
  for (j = 0; j < 1000; j++) {
    for (i = 0; i < ARR_SIZE; i+=4) { dummy = arr[i]; }
  }
  timer_stop();

  timer_start();
  for (j = 0; j < 1000; j++) {
    for (i = 0; i < ARR_SIZE; i+=1024) { dummy = arr[i]; }
  }
  timer_stop();

  exit(0);
}
