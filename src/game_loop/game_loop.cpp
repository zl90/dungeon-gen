#include "../include/game_loop.hpp"

void game_loop() {
  bool running = true;
  Grid g(84, 36);

  keypad(stdscr, TRUE);

  g.draw();
  refresh();

  while (running) {
    // Process input
    int input = getch();

    switch (input) {
    case 'q':
      running = false;
      break;
    case KEY_UP:
      g.cursor_up();
      break;
    case KEY_DOWN:
      g.cursor_down();
      break;
    case KEY_RIGHT:
      g.cursor_right();
      break;
    case KEY_LEFT:
      g.cursor_left();
      break;
    default:
      break;
    }

    // Update game state?

    // Render
    g.draw();
    refresh();

    // Simulate fixed time step (16ms, approx 60fps)
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
}