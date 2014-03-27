#include "types.h"
#include "stat.h"
#include "user.h"
#include "signal.h"

#define TIMES 1000

int count = 0;

void __wrapper(void);

void
sig_handler(void)
{
  printf(1, "In sig_handler, %d\n", count);
  if (count++ > TIMES) {
    asm("movl (%ebp), %eax");
    asm("movl 8(%eax), %edx");
    asm("add $6, %edx");
    asm("movl %edx, 8(%eax)");
  }
}

int
main(int argc, char **argv)
{
  signal(-1, __wrapper);
  signal(SIGSEGV, sig_handler);

  int start = uptime();
  printf(1, "%p\n", *(&argc - 1000000000));
  int stop = uptime();

  int time = (stop - start) * 100;  // in milliseconds
  printf(1, "%d exceptions took %d ms\n", TIMES, time);
  exit();
}
