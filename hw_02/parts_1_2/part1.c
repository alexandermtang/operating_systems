#include <stdio.h>
#include <signal.h>
#include "my_timer.h"

#define TOTAL_TIMES 1000  // number of times to execute handler

typedef void (*sig_t)(int);

int num_times = 0;  // current number of times handler is called

void sig_handler(int signo)
{
  char buffer[32];
  if (signo == SIGFPE) {
    num_times++;

    if (num_times > TOTAL_TIMES) {
      // use memcpy for stack buffer overflow
      return;
    }
  }
}

int main(int argc, char **argv)
{
  signal(SIGFPE, sig_handler);
  signal(SIGINT, sig_handler);

  timer_start();

  int zero = 0;
  int x = 0 / zero;  // force SIGFPE signal

  unsigned long long t = timer_stop();

  unsigned long long avg = t / TOTAL_TIMES;
  printf("avg time of exception handler: %llu\n", avg);

  return 0;
}
