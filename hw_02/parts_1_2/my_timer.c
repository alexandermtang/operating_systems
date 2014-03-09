#include <stdio.h>
#include <sys/time.h>
#include "my_timer.h"

struct timeval t_i, t_f;

void timer_start(void)
{
  gettimeofday(&t_i, NULL);
}

// return elapsed time in usec
unsigned long long timer_stop(void)
{
  gettimeofday(&t_f, NULL);

  unsigned long long s, us, t;
  s = t_f.tv_sec - t_i.tv_sec;
  us = t_f.tv_usec - t_i.tv_usec;
  t = 1000000 * s + us;
  /*printf("%llu us\n", t);*/

  return t;
}
