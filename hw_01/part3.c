#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "my_timer.h"

#define NUM_ITERS 1000
#define CHUNK_SIZE 1024 // send data in chunks of 1024 bytes

int main(int argc, char** argv)
{
  if (argc < 2) {
    printf("Error: usage: ./part3 <size-in-MB>\n");
    exit(-1);
  }

  unsigned long long block_size_MB = (int)strtol(argv[1], NULL, 10);
  unsigned long long block_size_B = block_size_MB * 1024 * 1024; // convert from MB to B
  unsigned long long num_chunks = block_size_B / CHUNK_SIZE;

  int p2c[2]; // parent to child pipe
  int c2p[2]; // child to parent pipe

  unsigned long long pipe_times[NUM_ITERS];

  int i, j;
  for (i = 0; i < NUM_ITERS; i++) {
    pipe(p2c);
    pipe(c2p);

    int pid = fork();
    timer_start();
    if (pid == 0) {
      // child
      close(p2c[1]);
      close(c2p[0]);

      char *block = malloc(block_size_B);

      for (j = 0; j < num_chunks; j++) {
        read(p2c[0], &block[j * CHUNK_SIZE], CHUNK_SIZE);
      }
      for (j = 0; j < num_chunks; j++) {
        write(c2p[1], &block[j * CHUNK_SIZE], CHUNK_SIZE);
      }
      free(block);

      close(p2c[0]);
      close(c2p[1]);
      exit(0);
    } else {
      // parent
      close(p2c[0]);
      close(c2p[1]);

      char *block = malloc(block_size_B);
      for (j = 0; j < block_size_B; j++) { block[j] = 'a'; }

      for (j = 0; j < num_chunks; j++) {
        write(p2c[1], &block[j * CHUNK_SIZE], CHUNK_SIZE);
      }
      for (j = 0; j < num_chunks; j++) {
        read(c2p[0], &block[j * CHUNK_SIZE], CHUNK_SIZE);
      }
      waitpid(pid, NULL, 0);
      free(block);

      close(p2c[1]);
      close(c2p[0]);
    }
    unsigned long long t = timer_stop();
    pipe_times[i] = t;
  }

  // compute avg cost of pipe communication
  double pipe_avg = 0.0;
  for (i = 0; i < NUM_ITERS; i++) { pipe_avg += pipe_times[i]; }
  pipe_avg /= NUM_ITERS;

  printf("avg cost of pipe communication for %llu MB block: %f usec\n",
      block_size_MB, pipe_avg);

  exit(0);
}
