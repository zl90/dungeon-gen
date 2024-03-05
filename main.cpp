#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>
#include <locale.h>
#include <memory>
#include <ncurses.h>
#include <random>
#include <time.h>

#include "grid.hpp"

void initialise_colours() {
  init_color(COLOR_BLUE, 0, 300, 1000);
  init_color(COLOR_CYAN, 100, 300, 100);
  init_color(COLOR_YELLOW, 350, 175, 0);
  init_color(COLOR_GREEN, 300, 500, 150);
  init_color(COLOR_WHITE, 200, 200, 200);
  init_color(COLOR_MAGENTA, 600, 50, 180);

  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_BLUE, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
}

int main() {
  setlocale(LC_ALL, "");
  std::srand(time(nullptr));

  initscr();

  start_color();
  initialise_colours();

  int input;

  while (input != 'q' && input != 27) {
    Grid g(128, 32);
    g.draw();

    refresh();

    input = getch();
  }

  refresh();

  endwin();

  return 0;
}
