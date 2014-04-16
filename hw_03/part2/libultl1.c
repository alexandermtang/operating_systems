#include "libult.h"

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

typedef struct {
  ucontext_t context;
  int active;
  void *stack;
} mypthread_t;

mypthread_t thread_list[MAX_THREADS];
int current_thread = -1;
int in_thread = 0;
int num_threads = 0;

ucontext_t scheduler;

int mypthread_run(void *(*func)(void *), void *arg)
{
  thread_list[current_thread].active = 1;
  func(arg);
  thread_list[current_thread].active = 0;

  mypthread_yield();
}

int mypthread_create(void *(*func)(void *), void *arg)
{
  if (num_threads == MAX_THREADS) return ERR_MAXTHREADS;

  getcontext(&thread_list[num_threads].context);

  thread_list[num_threads].context.uc_link = 0;
  thread_list[num_threads].stack = malloc(THREAD_STACK_SIZE);
  thread_list[num_threads].context.uc_stack.ss_sp = thread_list[num_threads].stack;
  thread_list[num_threads].context.uc_stack.ss_size = THREAD_STACK_SIZE;
  thread_list[num_threads].context.uc_stack.ss_flags = 0;

  if (thread_list[num_threads].stack == 0) return ERR_MALLOC;

  makecontext(&thread_list[num_threads].context, mypthread_run, 2, &func, arg);
  num_threads++;

  return NOERROR;
}

int mypthread_exit()
{

}

int mypthread_yield()
{

}
