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

  void map_terrain_();

  void set_colour_for_item(GridItem item);

  void unset_colour();
};