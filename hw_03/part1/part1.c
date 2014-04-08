#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define n 30

int a[n + 1], sorted = 0;
int *indices[n];
pthread_t threads[n], checker;
pthread_mutex_t mutexes[n + 1];

void *compare_and_swap(void *arg);
void *check_if_sorted(void *arg);

void print_a(void) {
  int i = 0;
  for (i = 0; i < n + 1; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

void init(void)
{
  int i = 0;
  for (i = 0; i < n + 1; i++) {
    a[i] = rand() % 100;
  }
  print_a();

  for (i = 0; i < n + 1; i++) {
    pthread_mutex_init(&mutexes[i], NULL);
  }

  for (i = 0; i < n; i++) {
    indices[i] = malloc(sizeof(int));
    *indices[i] = i;
    pthread_create(&threads[i], NULL, &compare_and_swap, (void *) indices[i]);
  }
  pthread_create(&checker, NULL, &check_if_sorted, NULL);
}

void cleanup(void)
{
  int i = 0;
  for (i = 0; i < n; i++) {
    pthread_join(threads[i], NULL);
  }
  for (i = 0; i < n + 1; i++) {
    pthread_mutex_destroy(&mutexes[i]);
  }
  for (i = 0; i < n; i++) {
    free(indices[i]);
  }
}

void *compare_and_swap(void *arg)
{
  int i = *(int *)arg;
  while (!sorted) {
    pthread_mutex_lock(&mutexes[i]);
    pthread_mutex_lock(&mutexes[i + 1]);
    if (a[i + 1] > a[i]) {
      int temp = a[i];
      a[i] = a[i + 1];
      a[i + 1] = temp;
    }
    pthread_mutex_unlock(&mutexes[i]);
    pthread_mutex_unlock(&mutexes[i + 1]);
  }
  return NULL;
}

void *check_if_sorted(void *arg) {
  int i = 0;
  for (i = 0; i < n; i++) {
    while (a[i + 1] > a[i]);
  }
  sorted = 1;
  return NULL;
}

int main(void)
{
  init();
  cleanup();
  print_a();

  return 0;
}
