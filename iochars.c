#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

void b() { printf("exiting"); }

int main(int argc, char *argv[]) {

  atexit(b);

  char a[10];
  while (1) {
    scanf("%s", a);
    printf("%s", a);
    if (a[0] == 'x') {
      break;
    }
  }

  return EXIT_SUCCESS;
}
