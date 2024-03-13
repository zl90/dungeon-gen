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
  void map_grass_terrain_();
  void map_frozen_terrain_();
  void map_fortresses_();
  void map_settlements_();
  void map_caves_();
  void map_inns_();
  void map_bridges_();
  void map_mage_towers_();
  void map_libraries_();
  void map_trolls_dens_();
  void map_pits_();

  GridItem generate_mountain_terrain_();
  GridItem generate_frozen_tundra_terrain_();
  GridItem generate_desert_terrain_();
  GridItem generate_barren_plains_terrain_();
  GridItem generate_grassy_plains_terrain_();
  GridItem generate_chaparral_terrain_();
  GridItem generate_foothill_terrain_();
  GridItem generate_ocean_terrain_();
  GridItem generate_forest_terrain_();

  void set_colour_for_item_(GridItem item);

  void unset_colour_();
};