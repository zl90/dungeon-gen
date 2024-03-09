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

std::unordered_map<ColourType, Colour> GridItem::colours = {
    {ColourType::White, {900, 900, 900, 1}},
    {ColourType::Blue, {50, 403, 768, 2}},
    {ColourType::Light_Blue, {690, 874, 843, 3}},
    {ColourType::Red, {1000, 133, 133, 4}},
    {ColourType::Pink, {1000, 431, 733, 5}},
    {ColourType::Purple, {400, 0, 1000, 6}},
    {ColourType::Orange, {1000, 400, 0, 7}},
    {ColourType::Yellow, {1000, 854, 352, 8}},
    {ColourType::Green, {266, 619, 207, 9}},
    {ColourType::Light_Green, {513, 831, 321, 10}},
    {ColourType::Grey, {333, 333, 333, 11}},
    {ColourType::Beige, {666, 700, 600, 12}},
    {ColourType::Brown, {480, 368, 184, 13}},
    {ColourType::Light_Pink, {1000, 654, 964, 14}},
};

Grid::Grid(unsigned int width, unsigned int height)
    : terrain_heatmap_(width, height), width_(width), height_(height) {

  GridItem ocean;
  ocean.icon = Terrain::terrain_icons[TerrainType::Ocean];
  ocean.colour = GridItem::colours[ColourType::Blue];
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
        mountain.colour = GridItem::colours[ColourType::Grey];
        Terrain mountain_terrain;
        mountain_terrain.type = TerrainType::Mountain;
        mountain_terrain.temperature = TemperatureType::Frigid;
        mountain.terrain = mountain_terrain;

        items_[i][j] = mountain;
      } else if (terrain_heatmap_[i][j] > 0.6f) {
        GridItem foothill;
        foothill.icon = Terrain::terrain_icons[TerrainType::Foothill];
        foothill.colour = GridItem::colours[ColourType::Beige];
        Terrain foothill_terrain;
        foothill_terrain.type = TerrainType::Foothill;
        foothill_terrain.temperature = TemperatureType::Cold;
        foothill.terrain = foothill_terrain;

        items_[i][j] = foothill;
      } else if (terrain_heatmap_[i][j] > 0.05f) {
        GridItem conifer_forest;
        conifer_forest.icon =
            Terrain::terrain_icons[TerrainType::Conifer_Forest];
        conifer_forest.colour = GridItem::colours[ColourType::Green];
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
  int r = item.colour.r;
  int g = item.colour.g;
  int b = item.colour.b;
  selected_colour_pair_ = item.colour.colour_pair_number;

  const int CUSTOM_COLOR = COLOR_WHITE + selected_colour_pair_;
  init_color(CUSTOM_COLOR, r, g, b);
  init_pair(selected_colour_pair_, CUSTOM_COLOR, COLOR_BLACK);

  attron(COLOR_PAIR(selected_colour_pair_));
}

void Grid::unset_colour() {
  attroff(COLOR_PAIR(selected_colour_pair_));
  selected_colour_pair_ = 1;
}
