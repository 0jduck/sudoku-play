// main.c

// ---- file setup ----
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "ui.h"

// ---- exit ----
struct termios terminal;
void restore(void) {
  tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
  printf("\x1b[?1049l");
  fflush(stdout);
}
void exitblock(int sig) { (void)sig; }
// ---- main ----
int main(int argc, char **argv) {
  // block ^C
  struct sigaction exit = {0};
  exit.sa_handler = exitblock;
  sigaction(SIGINT, &exit, NULL);
  // restore
  atexit(restore);
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  terminal = t;
  // change terminal
  t.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
  // change buffre
  printf("\x1b[?1049h");
  fflush(stdout);
  // test sudoku
  int sudoku[9][9] = {
      {5, 3, 0, 0, 7, 0, 0, 0, 0}, {6, 0, 0, 1, 9, 5, 0, 0, 0},
      {0, 9, 8, 0, 0, 0, 0, 6, 0}, {8, 0, 0, 0, 6, 0, 0, 0, 3},
      {4, 0, 0, 8, 0, 3, 0, 0, 1}, {7, 0, 0, 0, 2, 0, 0, 0, 6},
      {0, 6, 0, 0, 0, 0, 2, 8, 0}, {0, 0, 0, 4, 1, 9, 0, 0, 5},
      {0, 0, 0, 0, 8, 0, 0, 7, 9},
  };
  draw(sudoku);
  // wait loop
  char c;
  while ((c = getchar()) != 'x')
    ;
  // clean
  (void)argc;
  (void)argv;
  return 0;
}
