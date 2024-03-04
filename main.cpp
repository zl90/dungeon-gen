#include <memory>
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include "heatmap.h"
#include <iostream>
#include <locale.h>
#include <ncurses.h>
#include <random>
#include <stdio.h>
#include <string>
#include <time.h>
#include <wchar.h>

enum class Grid_Item {
  floor,
  wall_horizontal,
  wall_vertical,
  brush,
  grass,
  blank,
  water,
  stone,
  crack,
  cliff_wall,
  underground_stone,
  water_2
};

constexpr std::array<const wchar_t *, 13> grid_symbols = {
    L"¨", L"=", L"|", L",", L"\"", L" ", L"~", L"•", L".", L"▓", L"%", L"˜"};

class Grid {
public:
  Grid(unsigned int width, unsigned int height)
      : terrain_heatmap_(width, height), width_(width), height_(height) {

    items_ = std::vector<std::vector<Grid_Item>>(
        width, std::vector<Grid_Item>(height, Grid_Item::floor));

    // generate_ground_tiles();
    // generate_river_tiles();
    // generate_mountain_tiles();
    map_terrain_();
  }

  void draw() {
    int row, col;
    getmaxyx(stdscr, row, col);

    for (int y = 0; y < items_[0].size(); y++) {
      for (int x = 0; x < items_.size(); x++) {
        set_colour_for_item(items_[x][y]);
        mvaddwstr(row / 2 - y + items_[0].size() / 2,
                  col / 2 - items_.size() / 2 + x,
                  grid_symbols[(int)items_[x][y]]);
        unset_colour();
      }

      addch('\n');
    }
  }

private:
  unsigned int width_;
  unsigned int height_;

  std::vector<std::vector<Grid_Item>> items_;

  uint8_t selected_colour_pair_ = 1;

  HeatMap terrain_heatmap_;

  void map_terrain_() {
    for (unsigned int i = 0; i < width_; i++) {
      for (unsigned int j = 0; j < height_; j++) {
        if (terrain_heatmap_[i][j] > 0.8f) {
          items_[i][j] = get_random_underground_item();
        } else if (terrain_heatmap_[i][j] > 0.4f) {
          items_[i][j] = Grid_Item::cliff_wall;
        } else {
          items_[i][j] = get_random_ground_item();
        }
      }
    }
  }

  Grid_Item get_random_ground_item() {
    const uint8_t random_int = std::rand() % 6;
    switch (random_int) {
    case 0:
      return Grid_Item::floor;
    case 1:
      return Grid_Item::brush;
    case 2:
      return Grid_Item::grass;
    case 3:
      return Grid_Item::floor;
    case 4:
      return Grid_Item::stone;
    default:
      return Grid_Item::blank;
    }
  }

  Grid_Item get_random_underground_item() {
    const uint8_t random_int = std::rand() % 120;
    switch (random_int) {
    case 0:
      return Grid_Item::crack;
    case 1:
      return Grid_Item::underground_stone;
    default:
      return Grid_Item::blank;
    }
  }

  Grid_Item get_random_water_tile() {
    const short random_int = rand() % 2;
    if (random_int) {
      return Grid_Item::water;
    }
    return Grid_Item::water_2;
  }

  bool is_water_tile(int x, int y) {
    return items_[x][y] == Grid_Item::water ||
           items_[x][y] == Grid_Item::water_2;
  }

  bool is_above_river_tile(int x, int y) {
    if (x == 0) {
      return is_water_tile(x, y - 1) || is_water_tile(x + 1, y - 1);
    } else if (x == items_.size() - 1) {
      return is_water_tile(x, y - 1) || is_water_tile(x - 1, y - 1);
    } else {
      return is_water_tile(x, y - 1) || is_water_tile(x - 1, y - 1) ||
             is_water_tile(x + 1, y - 1);
    }
  }

  void generate_ground_tiles() {
    for (int x = 0; x < items_.size(); x++) {
      for (int y = 0; y < items_[x].size(); y++) {
        items_[x][y] = get_random_ground_item();
      }
    }
  }

  void generate_river_tiles() {
    for (int y = 0; y < items_[0].size(); y++) {
      if (y == 0) {
        const uint8_t random_int = rand() % items_.size();
        items_[random_int][y] = get_random_water_tile();
      } else {
        for (int x = 0; x < items_.size(); x++) {
          if (is_above_river_tile(x, y)) {
            if (rand() % 2 == 1) {
              items_[x][y] = get_random_water_tile();
            }
          }
        }
      }
    }
  }

  void generate_mountain_tiles() {
    int previous_cliff_x = 0;
    for (int y = 0; y < items_[0].size(); y++) {
      if (y == 0) {
        const uint8_t random_int = rand() % items_.size();
        items_[random_int][y] = Grid_Item::cliff_wall;
        previous_cliff_x = random_int;
        for (int x = previous_cliff_x - 1; x >= 0; x--) {
          if (previous_cliff_x - x > 4) {
            items_[x][y] = get_random_underground_item();
          } else {
            items_[x][y] = Grid_Item::blank;
          }
        }
      } else {
        short random_int = rand() % 5 - 2;
        int new_cliff_x = previous_cliff_x + random_int;
        if (new_cliff_x >= 0 && new_cliff_x < items_.size()) {
          items_[new_cliff_x][y] = Grid_Item::cliff_wall;

          if (random_int < -1) {
            items_[new_cliff_x + 1][y] = Grid_Item::cliff_wall;
          }

          for (int x = new_cliff_x - 1; x >= 0; x--) {
            if (random_int > 1 && x == new_cliff_x - 1) {
              items_[x][y] = Grid_Item::cliff_wall;
            } else if (previous_cliff_x - x > 4) {
              items_[x][y] = get_random_underground_item();
            } else {
              items_[x][y] = Grid_Item::blank;
            }
          }
          previous_cliff_x = new_cliff_x;
        } else if (new_cliff_x < 0) {
          // Do nothing to the grid. TODO: fix it so this code block is not
          // required.
        } else if (new_cliff_x >= items_.size()) {
          for (int x = items_.size() - 1; x >= 0; x--) {
            items_[x][y] = get_random_underground_item();
          }
          previous_cliff_x = new_cliff_x;
        }
      }
    }
  }

  void set_colour_for_item(Grid_Item item) {
    switch (item) {
    case Grid_Item::stone:
      attron(COLOR_PAIR(1));
      selected_colour_pair_ = 1;
      break;
    case Grid_Item::grass:
      attron(COLOR_PAIR(2));
      selected_colour_pair_ = 2;
      break;
    case Grid_Item::floor:
      attron(COLOR_PAIR(3));
      selected_colour_pair_ = 3;
      break;
    case Grid_Item::brush:
      attron(COLOR_PAIR(4));
      selected_colour_pair_ = 4;
      break;
    case Grid_Item::water:
      attron(COLOR_PAIR(5));
      selected_colour_pair_ = 5;
      break;
    case Grid_Item::water_2:
      attron(COLOR_PAIR(5));
      selected_colour_pair_ = 5;
      break;
    case Grid_Item::cliff_wall:
      attron(COLOR_PAIR(6));
      selected_colour_pair_ = 6;
      break;
    case Grid_Item::crack:
      attron(COLOR_PAIR(6));
      selected_colour_pair_ = 6;
      break;
    case Grid_Item::underground_stone:
      attron(COLOR_PAIR(3));
      selected_colour_pair_ = 3;
      break;
    default:
      attron(COLOR_PAIR(1));
      selected_colour_pair_ = 1;
      break;
    }
  }

  void unset_colour() {
    attroff(COLOR_PAIR(selected_colour_pair_));
    selected_colour_pair_ = 1;
  }
};

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
