#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

static struct timeval t_i, t_f;

void start(void)
{
  gettimeofday(&t_i, NULL);
}

// return elapsed time in ms
unsigned long long stop(void)
{
  gettimeofday(&t_f, NULL);
  unsigned long long t = 1000 * (t_f.tv_sec - t_i.tv_sec)
      + (t_f.tv_usec - t_i.tv_usec) / 1000;
  printf("%llu ms\n", t);
  return t;
}


void init(void)
{
}

int main(int argc, char** argv)
{


  return 0;
}
