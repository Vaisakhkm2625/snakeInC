#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

static struct termios old_termios, new_termios;

void reset_termianl() {
  printf("\e[m"); // reset colors
  printf("\e[?25h");
  fflush(stdout);
  tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

void configure_terminal() {
  tcgetattr(STDIN_FILENO, &old_termios);
  new_termios = old_termios;
  new_termios.c_cflag &= ~(ICANON | ECHO);

  new_termios.c_cc[VMIN] = 0;
  new_termios.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

  printf("\e[?25l"); // hide cursor

  atexit(reset_termianl);
}

int main(int argc, char *argv[]) {
  configure_terminal();

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
