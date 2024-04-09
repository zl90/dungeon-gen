#include "../include/game_loop.hpp"

// @TODO: this will need to be made into a class eventually
void game_loop() {
  bool running = true;
  Grid g(84, 36);

  keypad(stdscr, TRUE);

  g.Draw();
  refresh();

  while (running) {
    // Process input
    int input = getch();

    switch (input) {
    case 'q':
      running = false;
      break;
    case KEY_UP:
      g.CursorUp();
      break;
    case KEY_DOWN:
      g.CursorDown();
      break;
    case KEY_RIGHT:
      g.CursorRight();
      break;
    case KEY_LEFT:
      g.CursorLeft();
      break;
    default:
      break;
    }

    // Update game state?

    // Render
    g.Draw();
    refresh();

    // Simulate fixed time step (16ms, approx 60fps)
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
}