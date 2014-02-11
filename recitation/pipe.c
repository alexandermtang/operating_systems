#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  int p[2];
  char *arv[2];
  arv[0] = "wc";
  arv[1] = 0;

  pipe(p);

  if (fork() == 0) {
    close(0);
    dup(p[0]);
    close(p[0]);
    close(p[1]);
    execv("/usr/bin/wc", arv);
  } else {
    write(p[1], "Hello world\n", 12);
    close(p[0]);
    close(p[1]);
  }
}
