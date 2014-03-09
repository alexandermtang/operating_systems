#include <stdio.h>
#include <signal.h>
#include "my_timer.h"

#define TOTAL_TIMES 100000  // number of times to execute handler

typedef void (*sig_t)(int);

int num_times = 0;  // current number of times handler is called

void sig_handler(int signo)
{
  if (signo == SIGFPE) {
    num_times++;

    if (num_times > TOTAL_TIMES) {
      *(&signo + 15) += 8;
    }
  }
}

int main(int argc, char **argv)
{
  signal(SIGFPE, sig_handler);

  timer_start();

  int zero = 0;
  int x = 0 / zero;  // force SIGFPE signal

  unsigned long long t = timer_stop();

  double avg = (t * 1.0)/ TOTAL_TIMES;
  printf("avg time of exception handler: %f us\n", avg);

  return 0;
}
