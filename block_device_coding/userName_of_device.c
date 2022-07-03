#include <stdio.h>
#include <unistd.h>

main() {
  char *user;

  if ((user = getlogin()) == NULL)
    perror("getlogin() error");
  else printf("getlogin() returned %s\n", user);
}
