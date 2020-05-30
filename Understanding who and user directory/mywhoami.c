#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

int main(){
  uid_t id;
  struct passwd *p;

  id = getuid();
  p = getpwuid(id);

  printf("%s\n", p->pw_name);

  return 1;
}

