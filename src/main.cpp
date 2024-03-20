#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include "./include/game_loop.hpp"
#include <iostream>
#include <locale.h>
#include <memory>
#include <ncurses.h>
#include <random>
#include <time.h>

int main() {
  setlocale(LC_ALL, "");
  std::srand(time(nullptr));

  initscr();

  start_color();

  game_loop();

  endwin();

  return 0;
}
