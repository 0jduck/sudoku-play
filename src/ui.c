// draw.c

// ---- file setup ----
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "ui.h"

// ---- math ----
int top(void) {
  int result;
  // get termianl size
  struct winsize ws;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  // math
  int bord = 8 + 9 + 2;
  result = (ws.ws_row - bord) / 2;
  return result;
}
int side(void) {
  int result;
  // get termianl size
  struct winsize ws;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  // math
  int bord = 8 + 9 + 2;
  result = (ws.ws_col - bord) / 2;
  return result;
}
// ---- move ----
void move(int x, int y) {
  // math
  x = (x * 2) + side();
  y = (y * 2) + top();
  // move
  printf("\033[%d;%dH", y, x);
  fflush(stdout);
}
// ---- space ----
void topSpace(void) {
  int size = top();
  for (int i = 0; i < size; i++)
    printf("\n");
}
void sideSpace(void) {
  int size = side();
  for (int i = 0; i < size; i++)
    printf(" ");
}
// ---- draw ----
void boxStart(void) {
  // empty space
  sideSpace();
  // box
  printf("┌");
  for (int i = 0; i < 9; i++) {
    printf("─");
    if (i < 8)
      printf("┬");
  }
  printf("┐\n");
}
void boxEnd(void) {
  // empty space
  sideSpace();
  // box
  printf("└");
  for (int i = 0; i < 9; i++) {
    printf("─");
    if (i < 8)
      printf("┴");
  }
  printf("┘\n");
}
void boxLine(int line[9]) {
  // empty space
  sideSpace();
  // line
  printf("│");
  for (int i = 0; i < 9; i++) {
    if (line[i] == 0)
      printf(" │");
    else
      printf("%i│", line[i]);
  }
  printf("\n");
}
void draw(int sudoku[9][9]) {
  // empty space
  topSpace();
  // box start
  boxStart();
  // lines
  for (int i = 0; i < 9; i++) {
    boxLine(sudoku[i]);
    if (i < 8) {
      sideSpace();
      printf("├─┼─┼─┼─┼─┼─┼─┼─┼─┤\n");
    }
  }
  // box end
  boxEnd();
  // fflush
  fflush(stdout);
  // move
  move(1, 1);
}
