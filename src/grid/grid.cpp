#include <array>
#include <ncurses.h>
#include <random>
#include <vector>
#include <wchar.h>

#include "../include/grid.hpp"
#include "../include/grid_item.hpp"
#include "../include/heatmap.hpp"
#include "../include/terrain.hpp"

constexpr std::array<const wchar_t *, 13> grid_symbols = {
    L"¶", L"º", L"|", L",", L"\"", L" ", L"~", L"•", L"º", L"▓", L"%", L"˜",
};

Grid::Grid(unsigned int width, unsigned int height)
    : terrain_heatmap_(width, height), width_(width), height_(height) {

  GridItem ocean;
  ocean.icon = Terrain::terrain_icons[TerrainType::Ocean];
  Terrain ocean_terrain;
  ocean_terrain.type = TerrainType::Ocean;
  ocean_terrain.temperature = TemperatureType::Cold;
  ocean.terrain = ocean_terrain;

  items_ = std::vector<std::vector<GridItem>>(
      width, std::vector<GridItem>(height, ocean));

  map_terrain_();
}

void Grid::draw() {
  int row, col;
  getmaxyx(stdscr, row, col);

  for (int y = 0; y < items_[0].size(); y++) {
    for (int x = 0; x < items_.size(); x++) {
      set_colour_for_item(items_[x][y]);
      mvaddwstr(row / 2 - y + items_[0].size() / 2,
                col / 2 - items_.size() / 2 + x, items_[x][y].icon);
      unset_colour();
    }

    addch('\n');
  }
}

void Grid::map_terrain_() {
  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (terrain_heatmap_[i][j] > 0.9f) {
        GridItem mountain;
        mountain.icon = Terrain::terrain_icons[TerrainType::Mountain];
        Terrain mountain_terrain;
        mountain_terrain.type = TerrainType::Mountain;
        mountain_terrain.temperature = TemperatureType::Frigid;
        mountain.terrain = mountain_terrain;

        items_[i][j] = mountain;
      } else if (terrain_heatmap_[i][j] > 0.05f) {
        GridItem conifer_forest;
        conifer_forest.icon =
            Terrain::terrain_icons[TerrainType::Conifer_Forest];
        Terrain conifer_forest_terrain;
        conifer_forest_terrain.type = TerrainType::Conifer_Forest;
        conifer_forest_terrain.temperature = TemperatureType::Temperate;
        conifer_forest.terrain = conifer_forest_terrain;

        items_[i][j] = conifer_forest;
      }
    }
  }
}

void Grid::set_colour_for_item(GridItem item) {
  // switch (item) {
  // case Grid_Item::stone:
  //   attron(COLOR_PAIR(1));
  //   selected_colour_pair_ = 1;
  //   break;
  // case Grid_Item::grass:
  //   attron(COLOR_PAIR(2));
  //   selected_colour_pair_ = 2;
  //   break;
  // case Grid_Item::floor:
  //   attron(COLOR_PAIR(3));
  //   selected_colour_pair_ = 3;
  //   break;
  // case Grid_Item::brush:
  //   attron(COLOR_PAIR(4));
  //   selected_colour_pair_ = 4;
  //   break;
  // case Grid_Item::water:
  //   attron(COLOR_PAIR(5));
  //   selected_colour_pair_ = 5;
  //   break;
  // case Grid_Item::water_2:
  //   attron(COLOR_PAIR(5));
  //   selected_colour_pair_ = 5;
  //   break;
  // case Grid_Item::cliff_wall:
  //   attron(COLOR_PAIR(6));
  //   selected_colour_pair_ = 6;
  //   break;
  // case Grid_Item::crack:
  //   attron(COLOR_PAIR(6));
  //   selected_colour_pair_ = 6;
  //   break;
  // case Grid_Item::underground_stone:
  //   attron(COLOR_PAIR(3));
  //   selected_colour_pair_ = 3;
  //   break;
  // default:
  //   attron(COLOR_PAIR(1));
  //   selected_colour_pair_ = 1;
  //   break;
  // }
}

void Grid::unset_colour() {
  attroff(COLOR_PAIR(selected_colour_pair_));
  selected_colour_pair_ = 1;
}
