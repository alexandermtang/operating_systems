#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int pid = fork();
  printf("Hello, world from %d\n", pid);
  pid = fork();
  printf("Hello, again from %d\n", pid);

  return 0;
}
