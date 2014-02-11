#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int pid;

  if (argc < 2) {
    printf("Need arg\n");
    return -1;
  }

  char *cmd = argv[1];
  pid = fork();

  if (pid == 0) {
    printf("child execing %s\n", cmd);
    char *args[] = {"sh", "-c", cmd, NULL};
    execvp("sh", args);
  } else {
    printf("execed %s in another process\n", cmd);
  }



  return 0;
}
