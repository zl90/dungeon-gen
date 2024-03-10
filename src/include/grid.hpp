#pragma once
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "grid_item.hpp"
#include "heatmap.hpp"

class Grid {
public:
  Grid(unsigned int width, unsigned int height);
  void draw();

private:
  unsigned int width_;
  unsigned int height_;

  std::vector<std::vector<GridItem>> items_;

  uint8_t selected_colour_pair_ = 1;

  HeatMap terrain_heatmap_;

  void map_basic_terrain_();
  void map_desert_terrain_();

  GridItem generate_mountain_grid_item();
  GridItem generate_desert_grid_item();
  GridItem generate_foothill_grid_item();
  GridItem generate_ocean_grid_item();
  GridItem generate_forest_grid_item();

  void set_colour_for_item(GridItem item);

  void unset_colour();
};