#include <stdio.h>
#include <stdlib.h>

#include "mypthread.h"

#define n 5

mypthread_t hi_thread, bye_thread;

void *hi(void *arg);
void *bye(void *arg);

void init(void)
{
  mypthread_create(&hi_thread, &hi, NULL);
  mypthread_create(&bye_thread, &bye, NULL);
}

void cleanup(void)
{
  mypthread_join(&hi_thread);
  mypthread_join(&bye_thread);
}

void *hi(void *arg)
{
  printf("hi\n");
  return NULL;
}

void *bye(void *arg)
{
  printf("bye\n");
  return NULL;
}

int main(void)
{
  init();
  cleanup();

  return 0;
}
