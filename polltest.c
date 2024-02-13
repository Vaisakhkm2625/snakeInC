#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {

  char c;

  struct termios oldattr, newattr;

  // Get current terminal attributes
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  // Disable canonical mode and echoing
  newattr.c_lflag &= ~(ICANON | ECHO);
  // Set new terminal attributes
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

  printf("Enter a character: ");

  // Read a single character
  c = getchar();

  // Restore old terminal attributes
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

  // Use the character
  printf("\nYou entered: %c\n", c);

  // Resume the program immediately without waiting for further input
  // Program logic here...

  return 0;
}
