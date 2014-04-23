#include <stdio.h>
#include <stdlib.h>

#include "mypthread.h"

#define n 5

int a[n + 1], sorted = 0;
int *indices[n];
mypthread_t threads[n], checker;
mypthread_mutex_t mutexes[n + 1];

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
    a[i] = i;
  }

  for (i = 0; i < n + 1; i++) {
    mypthread_mutex_init(&mutexes[i]);
  }

  for (i = 0; i < n; i++) {
    indices[i] = malloc(sizeof(int));
    *indices[i] = i;
    mypthread_create(&threads[i], &compare_and_swap, (void *) indices[i]);
  }
  mypthread_create(&checker, &check_if_sorted, NULL);
}

void cleanup(void)
{
  int i = 0;
  for (i = 0; i < n; i++) {
    mypthread_join(&threads[i]);
  }
  for (i = 0; i < n + 1; i++) {
    mypthread_mutex_destroy(&mutexes[i]);
  }
  for (i = 0; i < n; i++) {
    free(indices[i]);
  }
}

void *compare_and_swap(void *arg)
{
  int i = *(int *)arg;
  while (!sorted) {
    mypthread_mutex_lock(&mutexes[i]);
    mypthread_mutex_lock(&mutexes[i + 1]);
    if (a[i + 1] > a[i]) {
      int temp = a[i];
      a[i] = a[i + 1];
      a[i + 1] = temp;
    }
    mypthread_mutex_unlock(&mutexes[i]);
    mypthread_mutex_unlock(&mutexes[i + 1]);
  }
  return NULL;
}

// how to foolproof check?
void *check_if_sorted(void *arg) {
  int i = 0;
  for (i = 0; i < n; i++) {
    if (a[i + 1] > a[i]) {
      i = 0;
    }
  }
  sorted = 1;
  return NULL;
}

int main(void)
{
  init();
  printf("unsorted: ");
  print_a();
  cleanup();
  printf("  sorted: ");
  print_a();

  return 0;
}
