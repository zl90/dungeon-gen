#include <array>
#include <ncurses.h>
#include <random>
#include <vector>
#include <wchar.h>

#include "grid.hpp"
#include "heatmap.hpp"

constexpr std::array<const wchar_t *, 13> grid_symbols = {
    L"¨", L"=", L"|", L",", L"\"", L" ", L"~", L"•", L".", L"▓", L"%", L"˜"};

Grid::Grid(unsigned int width, unsigned int height)
    : terrain_heatmap_(width, height), width_(width), height_(height) {

  items_ = std::vector<std::vector<Grid_Item>>(
      width, std::vector<Grid_Item>(height, Grid_Item::floor));

  map_terrain_();
}

void Grid::draw() {
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

void Grid::map_terrain_() {
  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (terrain_heatmap_[i][j] > 0.6f) {
        items_[i][j] = get_random_underground_item();
      } else if (terrain_heatmap_[i][j] > 0.2f) {
        items_[i][j] = Grid_Item::cliff_wall;
      } else {
        items_[i][j] = get_random_ground_item();
      }
    }
  }
}

Grid_Item Grid::get_random_ground_item() {
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

Grid_Item Grid::get_random_underground_item() {
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

Grid_Item Grid::get_random_water_tile() {
  const short random_int = rand() % 2;
  if (random_int) {
    return Grid_Item::water;
  }
  return Grid_Item::water_2;
}

void Grid::set_colour_for_item(Grid_Item item) {
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

void Grid::unset_colour() {
  attroff(COLOR_PAIR(selected_colour_pair_));
  selected_colour_pair_ = 1;
}
