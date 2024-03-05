#pragma once
#include "heatmap.hpp"
#include <cstdint>
#include <vector>

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

class Grid {
public:
  Grid(unsigned int width, unsigned int height);
  void draw();

private:
  unsigned int width_;
  unsigned int height_;

  std::vector<std::vector<Grid_Item>> items_;

  uint8_t selected_colour_pair_ = 1;

  HeatMap terrain_heatmap_;

  void map_terrain_();

  Grid_Item get_random_ground_item();

  Grid_Item get_random_underground_item();

  Grid_Item get_random_water_tile();

  bool is_water_tile(int x, int y);

  bool is_above_river_tile(int x, int y);

  void generate_ground_tiles();

  void generate_river_tiles();

  void generate_mountain_tiles();

  void set_colour_for_item(Grid_Item item);

  void unset_colour();
};