#include "../include/game_loop.hpp"

// @TODO: this will need to be made into a class eventually
auto GameLoop() -> void {
  bool running = true;
  Grid g(84, 36);

  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);  // Enable non-blocking input

  g.Draw();
  refresh();

  while (running) {
    int input = getch();

    if (input != ERR) {
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
        case 'i':
          g.InfoPanelCursorUp();
          break;
        case 'k':
          g.InfoPanelCursorDown();
          break;
        default:
          break;
      }
    }

    // Render
    g.Draw();
    refresh();

    // Simulate fixed time step (16ms, approx 60fps)
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
}