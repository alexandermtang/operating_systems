#define MAX_THREADS 10
#define THREAD_STACK_SIZE (1024*1024)

#define NOERROR 0
#define ERR_MALLOC -1
#define ERR_MAXTHREADS -2

int mypthread_create();
void mypthread_exit();
void mypthread_yield(void);
int mypthread_join(void);
