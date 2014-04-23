#include <stdlib.h>
#include <ucontext.h>

#include "mypthread.h"

mypthread_t thread_list[MAX_THREADS];
int current_thread = -1;
int in_thread = 0;
int num_threads = 0;

ucontext_t main_context;

void mypthread_run(void (*func)(void *), void *arg)
{
  thread_list[current_thread].active = 1;
  func(arg);
  thread_list[current_thread].active = 0;

  mypthread_yield();
}

int mypthread_create(mypthread_t *thread, void *(*func)(void *), void *arg)
{
  if (num_threads == MAX_THREADS) return ERR_MAXTHREADS;

  getcontext(&thread_list[num_threads].context);

  thread_list[num_threads].context.uc_link = 0;
  thread_list[num_threads].stack = malloc(THREAD_STACK_SIZE);
  thread_list[num_threads].context.uc_stack.ss_sp = thread_list[num_threads].stack;
  thread_list[num_threads].context.uc_stack.ss_size = THREAD_STACK_SIZE;
  thread_list[num_threads].context.uc_stack.ss_flags = 0;

  if (thread_list[num_threads].stack == 0) return ERR_MALLOC;

  *thread = thread_list[num_threads];
  makecontext(&thread_list[num_threads].context, (void (*)(void)) &mypthread_run, 2, func, arg); // not sure if right
  num_threads++;

  return NOERROR;
}

void mypthread_exit(void)
{
  thread_list[current_thread].active = 0;
  swapcontext(&thread_list[current_thread].context, &main_context);
}

int mypthread_join(mypthread_t thread)
{
  while (thread.active != 0) {
    mypthread_yield();
  }

  return NOERROR;
}

void mypthread_yield(void)
{
  if (in_thread) {
  // swap from thread to main_context
    swapcontext(&thread_list[current_thread].context, &main_context);
  } else {
  // in main_context, so dispatch another thread

   while (num_threads > 0) {
     current_thread = (current_thread + 1) % num_threads;

     in_thread = 1;
     swapcontext(&main_context, &thread_list[current_thread].context);
     in_thread = 0;

     if (thread_list[current_thread].active == 0) {
       // thread is finished executing, clean up
       free(thread_list[current_thread].stack);
       num_threads--;

       // current_thread is empty, swap with last one
       if (current_thread != num_threads) {
         thread_list[current_thread] = thread_list[num_threads];
       }
       thread_list[num_threads].active = 0;
     }
   }
  }
}

uint xchg(volatile uint *addr, uint newval)
{
  uint result;
  asm volatile("lock; xchgl %0, %1"
               : "+m" (*addr), "=a" (result)
               : "1" (newval)
               : "cc");
  return result;
}

int mypthread_mutex_init(mypthread_mutex_t *mutex)
{
  mutex->locked = 0;
  return 0;
}

int mypthread_mutex_lock(mypthread_mutex_t *mutex)
{
  while(xchg(&mutex->locked, 1) != 0);
  return 0;
}

int mypthread_mutex_trylock(mypthread_mutex_t *mutex)
{
  if(xchg(&mutex->locked, 1) == 0) {
    return 0;
  }
  return -1;
}

int mypthread_mutex_unlock(mypthread_mutex_t *mutex)
{
  xchg(&mutex->locked, 0);
  return 0;
}

int mypthread_mutex_destroy(mypthread_mutex_t *mutex)
{
  return 0;
}

