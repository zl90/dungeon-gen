#include "../include/game_loop.hpp"

// @TODO: this will need to be made into a class eventually
auto GameLoop() -> void {
  bool running = true;
  Grid g(84, 36);

  keypad(stdscr, TRUE);

  g.Draw();
  refresh();

  while (g.IsGameRunning()) {
    // Render
    g.Draw();
    refresh();
  }
}