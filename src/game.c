// game.c

// ---- file setup ----
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "ui.h"

#include "game.h"
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
    if (*y > 0)
      (*y)--;
    break;
  case 's':
    if (*y < 8)
      (*y)++;
    break;
  case 'a':
    if (*x > 0)
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
