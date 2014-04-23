#ifndef MYPTHREAD_H
#define MYPTHREAD_H

#define MAX_THREADS 100
#define THREAD_STACK_SIZE (1024*1024)

#define NOERROR 0
#define ERR_MALLOC -1
#define ERR_MAXTHREADS -2

#include <ucontext.h>
#include <stdlib.h>

enum threadstate { RUNNING, ZOMBIE };

typedef struct mypthread_t {
  ucontext_t context;
  enum threadstate state;
  void *stack;
} mypthread_t;

typedef struct mypthread_mutex_t {
   uint locked;
} mypthread_mutex_t;

int mypthread_create(mypthread_t *thread, void *(*func)(void *), void *arg);
void mypthread_exit(void);
int mypthread_join(mypthread_t thread);
void mypthread_yield(void);

int mypthread_mutex_init(mypthread_mutex_t *mutex);
int mypthread_mutex_lock(mypthread_mutex_t *mutex);
int mypthread_mutex_trylock(mypthread_mutex_t *mutex);
int mypthread_mutex_unlock(mypthread_mutex_t *mutex);
int mypthread_mutex_destroy(mypthread_mutex_t *mutex);

#endif
