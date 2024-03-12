#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>
#include <locale.h>
#include <memory>
#include <ncurses.h>
#include <random>
#include <time.h>

#include "./include/grid.hpp"

int main() {
  setlocale(LC_ALL, "");
  std::srand(time(nullptr));

  initscr();

  start_color();

  int input;

  while (input != 'q' && input != 27) {
    Grid g(84, 36);
    g.draw();

    refresh();

    input = getch();
  }

  refresh();

  endwin();

  return 0;
}
