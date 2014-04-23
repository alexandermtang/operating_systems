#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <signal.h>
#include <sys/time.h>
#include "mypthread.h"

mypthread_t *thread_list[MAX_THREADS]; // thread table
int current_thread = -1;               // index of current thread executing
int in_thread = 0;                     // 1 if executing in thread, 0 if in scheduler
int num_threads = 0;                   // number of RUNNING threads in table
ucontext_t scheduler;                  // context used to save scheduler

int first_thread = 1;                  // has first thread been created yet?
struct itimerval it;                   // timer value for scheduler timer
sigset_t set, oset;                    // set of signals disableed for process

void init_timer(void);
void schedule(int signum);
void disable_timer_int(void);
void enable_timer_int(void);

// Set up thread scheduling timer and signal handler for timer.
void init_timer(void)
{
  first_thread = 0;

  sigemptyset(&set);
  sigaddset(&set, SIGPROF);

  struct sigaction act, oact;
  act.sa_handler = schedule;
  sigaction(SIGPROF, &act, &oact);

  it.it_value.tv_usec = 100;
  it.it_interval.tv_usec = 100;      // SIGPROF fired every 100 usec
  setitimer(ITIMER_PROF, &it, NULL);

  // add main()'s context to list
  thread_list[num_threads] = malloc(sizeof(mypthread_t));
  getcontext(&thread_list[num_threads]->context);

  thread_list[num_threads]->context.uc_link = 0;
  thread_list[num_threads]->state = RUNNING;
  thread_list[num_threads]->stack = malloc(THREAD_STACK_SIZE);
  thread_list[num_threads]->context.uc_stack.ss_sp = thread_list[num_threads]->stack;
  thread_list[num_threads]->context.uc_stack.ss_size = THREAD_STACK_SIZE;
  thread_list[num_threads]->context.uc_stack.ss_flags = 0;
  num_threads++;
}

// Called when timer expires. Calls mypthread_yield().
void schedule(int signum)
{
  mypthread_yield();
}

// Disables timer interrupt. Called whenever executing library code.
void disable_timer_int(void)
{
  sigprocmask(SIG_BLOCK, &set, &oset);
}

// Enables timer interrupt.
void enable_timer_int(void)
{
  sigprocmask(SIG_SETMASK, &oset, NULL);
}

// Wrapper function for user thread which takes the last two arguments of
// pthread_create().
void mypthread_run(void (*func)(void *), void *arg)
{
  thread_list[current_thread]->state = RUNNING;
  enable_timer_int();

  func(arg);

  disable_timer_int();
  thread_list[current_thread]->state = ZOMBIE;

  mypthread_yield();
}

// Initialize user thread, uses pthread_run() as a helper function.
int mypthread_create(mypthread_t *thread, void *(*func)(void *), void *arg)
{
  disable_timer_int();
  if (num_threads == MAX_THREADS) {
    enable_timer_int();
    return ERR_MAXTHREADS;
  }

  thread_list[num_threads] = thread;

  getcontext(&thread_list[num_threads]->context);

  thread_list[num_threads]->context.uc_link = 0;
  thread_list[num_threads]->state = RUNNABLE;
  thread_list[num_threads]->stack = malloc(THREAD_STACK_SIZE);
  thread_list[num_threads]->context.uc_stack.ss_sp = thread_list[num_threads]->stack;
  thread_list[num_threads]->context.uc_stack.ss_size = THREAD_STACK_SIZE;
  thread_list[num_threads]->context.uc_stack.ss_flags = 0;

  makecontext(&thread_list[num_threads]->context, (void (*)(void)) &mypthread_run, 2, func, arg);
  num_threads++;

  if (first_thread) init_timer();

  enable_timer_int();
  return NOERROR;
}

// Exit by changing state to ZOMBIE and switching to scheduler, which will
// clean up the current thread.
void mypthread_exit(void)
{
  disable_timer_int();
  thread_list[current_thread]->state = ZOMBIE;
  swapcontext(&thread_list[current_thread]->context, &scheduler);
  enable_timer_int();
}

// Current thread yields until thread.state == ZOMBIE.
int mypthread_join(mypthread_t *thread)
{
  disable_timer_int();
  while (thread->state != ZOMBIE) {
    mypthread_yield();
  }
  enable_timer_int();
  return NOERROR;
}

// Called by schedule() whenever timer expires.
void mypthread_yield(void)
{
  disable_timer_int();
  if (in_thread) {
    // swap from current thread to scheduler
    swapcontext(&thread_list[current_thread]->context, &scheduler);
  } else {
    // in scheduler, so dispatch another thread
    while (num_threads > 1) {
      current_thread = (current_thread + 1) % num_threads;

      in_thread = 1;
      swapcontext(&scheduler, &thread_list[current_thread]->context);
      in_thread = 0;

      if (thread_list[current_thread]->state == ZOMBIE) {
        // thread is finished executing, clean up
        free(thread_list[current_thread]->stack);
        num_threads--;

        // current_thread is empty, swap with last one
        if (current_thread != num_threads) {
          thread_list[current_thread] = thread_list[num_threads];
        }
        thread_list[num_threads]->state = ZOMBIE;
      }
    }
    // disable timer
    timerclear(&it.it_value);
    enable_timer_int();
  }
}

uint xchg(volatile uint *addr, uint newval)
{
  disable_timer_int();
  uint result;
  asm volatile("lock; xchgl %0, %1"
               : "+m" (*addr), "=a" (result)
               : "1" (newval)
               : "cc");
  enable_timer_int();
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

