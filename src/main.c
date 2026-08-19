// main.c

// ---- file setup ----
#include "ui.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

// ---- game loop ----
void placeNumber(int sudoku[9][9], int sudokuUser[9][9], int x, int y, char c) {
  // place
  if (sudoku[y][x] == 0) {
    sudokuUser[y][x] = c - '0';
    if (sudokuUser[y][x] == 0)
      printf(" ");
    else
      printf("%c", c);
    move(x, y);
  }
}
void movePointer(int *x, int *y, char c) {
  switch (c) {
  case 'w':
    if (*y > 1)
      (*y)--;
    break;
  case 's':
    if (*y < 8)
      (*y)++;
    break;
  case 'a':
    if (*x > 1)
      (*x)--;
    break;
  case 'd':
    if (*x < 8)
      (*x)++;
    break;
  }
  move(*x, *y);
}
void game(int sudoku[9][9]) {
  // main variables
  int sudokuUser[9][9];
  memcpy(sudokuUser, sudoku, sizeof(sudokuUser));
  int x = 0;
  int y = 0;
  // input variables
  char exit = 27;
  char c;
  // input loop
  while ((c = getchar()) != exit) {
    if (c >= '0' && c <= '9')
      placeNumber(sudoku, sudokuUser, x, y, c);
    else
      movePointer(&x, &y, c);
  }
}
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
  game(sudoku);
  // clean
  (void)argc;
  (void)argv;
  return 0;
}
