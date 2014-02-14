#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "my_timer.h"

#define NUM_ITERS 10000

int main(int argc, char** argv)
{
  if (argc < 2) {
    printf("Error: usage: ./part2 <size-in-MB>\n");
    exit(-1);
  }

  unsigned long long fork_times[NUM_ITERS];

  unsigned long block_size_MB = (int)strtol(argv[1], NULL, 10);
  unsigned long block_size_B = block_size_MB * 1000; // convert from MB to B

  int i = 0, j = 0;

  for (i = 0; i < NUM_ITERS; i++) {

    // allocate memory for arr and initialize to 'a'
    char *arr = malloc(block_size_B);
    for (j = 0; j < block_size_B; j++) { arr[j] = 'a'; }

    timer_start();
    int pid = fork();
    if (pid == 0) {
      // child
      free(arr);
      exit(0);
    } else {
      // parent
      waitpid(pid, NULL, 0); // wait for child to return
      free(arr);
      unsigned long long t = timer_stop();
      fork_times[i] = t;
    }
  }

  // calculate avg cost of fork
  double fork_avg = 0.0;
  for (i = 0; i < NUM_ITERS; i++) { fork_avg += fork_times[i]; }
  fork_avg /= NUM_ITERS;

  printf("avg cost of fork for %lu MB block: %.2f usec\n", block_size_MB, fork_avg);

  exit(0);
}
