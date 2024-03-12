#include <array>
#include <ncurses.h>
#include <random>
#include <vector>
#include <wchar.h>

#include "../include/grid.hpp"
#include "../include/grid_item.hpp"
#include "../include/heatmap.hpp"
#include "../include/terrain.hpp"

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
  GridItem ocean = generate_ocean_terrain_();
  items_ = std::vector<std::vector<GridItem>>(
      width, std::vector<GridItem>(height, ocean));

  map_basic_terrain_();
  map_desert_terrain_();
  map_grass_terrain_();
  map_fortresses_();
  map_settlements_();
  map_caves_();
}

void Grid::draw() {
  int row, col;
  getmaxyx(stdscr, row, col);

  for (int y = 0; y < items_[0].size(); y++) {
    for (int x = 0; x < items_.size(); x++) {
      set_colour_for_item_(items_[x][y]);
      mvaddwstr(row / 2 - y + items_[0].size() / 2,
                col / 2 - items_.size() / 2 + x, +items_[x][y].icon);
      unset_colour_();
    }
    addch('\n');
  }
}

void Grid::map_basic_terrain_() {
  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (terrain_heatmap_[i][j] > 0.95f) {
        items_[i][j] = generate_mountain_terrain_();
      } else if (terrain_heatmap_[i][j] > 0.75f) {
        items_[i][j] = generate_foothill_terrain_();
      } else if (terrain_heatmap_[i][j] > 0.05f) {
        items_[i][j] = generate_forest_terrain_();
      }
    }
  }
}

void Grid::map_desert_terrain_() {
  HeatMap desert_heatmap(width_, height_);
  HeatMap barren_plains_heatmap(width_, height_);

  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (items_[i][j].terrain.type == TerrainType::Ash_Forest ||
          items_[i][j].terrain.type == TerrainType::Conifer_Forest ||
          items_[i][j].terrain.type == TerrainType::Pine_Forest)
        if (desert_heatmap[i][j] > 0.99f) {
          items_[i][j] = generate_desert_terrain_();
        }

      if (barren_plains_heatmap[i][j] > 0.99f &&
          items_[i][j].terrain.type == TerrainType::Sandy_Desert) {
        items_[i][j] = generate_barren_plains_terrain_();
      }
    }
  }
}

void Grid::map_grass_terrain_() {
  HeatMap grass_heatmap(width_, height_);
  HeatMap chaparral_heatmap(width_, height_);

  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (items_[i][j].terrain.type == TerrainType::Conifer_Forest ||
          items_[i][j].terrain.type == TerrainType::Pine_Forest)
        if (grass_heatmap[i][j] > 0.99f) {
          items_[i][j] = generate_grassy_plains_terrain_();
        }

      if (chaparral_heatmap[i][j] > 0.99f &&
          items_[i][j].terrain.type == TerrainType::Grassy_Plains) {
        items_[i][j] = generate_chaparral_terrain_();
      }
    }
  }
}

void Grid::map_frozen_terrain_() {
  HeatMap frozen_heatmap(width_, height_);

  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_ / 6; j++) {
      if (frozen_heatmap[i][j] > 0.95f &&
          items_[i][j].terrain.type != TerrainType::Ocean) {
        items_[i][j] = generate_frozen_tundra_terrain_();
      }
    }

    for (unsigned int j = height_ - (height_ / 6); j < height_; j++) {
      if (frozen_heatmap[i][j] > 0.95f &&
          items_[i][j].terrain.type != TerrainType::Ocean) {
        items_[i][j] = generate_frozen_tundra_terrain_();
      }
    }
  }
}

void Grid::map_fortresses_() {
  HeatMap fortress_heatmap(width_, height_, StructureType::Fortress, 5);

  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (fortress_heatmap[i][j] > 0.0f &&
          items_[i][j].terrain.type != TerrainType::Ocean) {
        items_[i][j].structure = Structure(StructureType::Fortress);
        items_[i][j].colour =
            GridItem::colours[ColourType::Beige]; // Unowned structures are
                                                  // Beige
        items_[i][j].icon = Structure::structure_icons[StructureType::Fortress];
      }
    }
  }
}

void Grid::map_settlements_() {
  HeatMap settlement_heatmap(width_, height_, StructureType::Settlement, 10);

  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (settlement_heatmap[i][j] > 0.0f &&
          items_[i][j].terrain.type != TerrainType::Ocean) {
        items_[i][j].structure = Structure(StructureType::Settlement);
        items_[i][j].colour =
            GridItem::colours[ColourType::Beige]; // Unowned structures are
                                                  // Beige
        items_[i][j].icon =
            Structure::structure_icons[StructureType::Settlement];
      }
    }
  }
}

void Grid::map_caves_() {
  HeatMap cave_heatmap(width_, height_, StructureType::Cave, 12);

  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (cave_heatmap[i][j] > 0.0f &&
          items_[i][j].terrain.type != TerrainType::Ocean) {
        items_[i][j].structure = Structure(StructureType::Cave);
        items_[i][j].colour = GridItem::colours[ColourType::Brown];

        items_[i][j].icon = Structure::structure_icons[StructureType::Cave];
      }
    }
  }
}

// @TODO: All of these generate_x_terrain functions should simply be done in the
// constructor of the Terrain class.
GridItem Grid::generate_mountain_terrain_() {
  int random_choice = rand() % 4;
  Colour colour;
  TemperatureType temperature;

  if (random_choice == 1) {
    colour = GridItem::colours[ColourType::Beige];
    temperature = TemperatureType::Frigid;
  } else {
    colour = GridItem::colours[ColourType::Grey];
    temperature = TemperatureType::Cold;
  }

  GridItem mountain;
  mountain.icon = Terrain::terrain_icons[TerrainType::Mountain];
  mountain.colour = colour;
  Terrain mountain_terrain;
  mountain_terrain.type = TerrainType::Mountain;
  mountain_terrain.temperature = temperature;
  mountain.terrain = mountain_terrain;
  return mountain;
}

GridItem Grid::generate_desert_terrain_() {
  GridItem desert;
  desert.icon = Terrain::terrain_icons[TerrainType::Sandy_Desert];
  desert.colour = GridItem::colours[ColourType::Yellow];
  Terrain desert_terrain;
  desert_terrain.type = TerrainType::Sandy_Desert;
  desert_terrain.temperature = TemperatureType::Hot;
  desert.terrain = desert_terrain;
  return desert;
}

GridItem Grid::generate_barren_plains_terrain_() {
  GridItem barren_plains;
  barren_plains.icon = Terrain::terrain_icons[TerrainType::Barren_Plains];
  barren_plains.colour = GridItem::colours[ColourType::Brown];
  Terrain barren_plains_terrain;
  barren_plains_terrain.type = TerrainType::Barren_Plains;
  barren_plains_terrain.temperature = TemperatureType::Hot;
  barren_plains.terrain = barren_plains_terrain;
  return barren_plains;
}

GridItem Grid::generate_frozen_tundra_terrain_() {
  GridItem frozen_tundra;
  frozen_tundra.icon = Terrain::terrain_icons[TerrainType::Frozen_Tundra];
  frozen_tundra.colour = GridItem::colours[ColourType::White];
  Terrain frozen_tundra_terrain;
  frozen_tundra_terrain.type = TerrainType::Frozen_Tundra;
  frozen_tundra_terrain.temperature = TemperatureType::Frigid;
  frozen_tundra.terrain = frozen_tundra_terrain;
  return frozen_tundra;
}

GridItem Grid::generate_grassy_plains_terrain_() {
  int random_choice = rand() % 2;
  TemperatureType temperature;

  if (random_choice == 1) {
    temperature = TemperatureType::Humid;
  } else {
    temperature = TemperatureType::Temperate;
  }

  GridItem grassy_plains;
  grassy_plains.icon = Terrain::terrain_icons[TerrainType::Grassy_Plains];
  grassy_plains.colour = GridItem::colours[ColourType::Light_Green];
  Terrain grassy_plains_terrain;
  grassy_plains_terrain.type = TerrainType::Grassy_Plains;
  grassy_plains_terrain.temperature = temperature;
  grassy_plains.terrain = grassy_plains_terrain;
  return grassy_plains;
}

GridItem Grid::generate_chaparral_terrain_() {
  int random_choice = rand() % 2;
  TemperatureType temperature;

  if (random_choice == 1) {
    temperature = TemperatureType::Humid;
  } else {
    temperature = TemperatureType::Temperate;
  }

  GridItem chaperral;
  chaperral.icon = Terrain::terrain_icons[TerrainType::Chaparral];
  chaperral.colour = GridItem::colours[ColourType::Light_Green];
  Terrain chaperral_terrain;
  chaperral_terrain.type = TerrainType::Chaparral;
  chaperral_terrain.temperature = temperature;
  chaperral.terrain = chaperral_terrain;
  return chaperral;
}

GridItem Grid::generate_foothill_terrain_() {
  GridItem foothill;
  foothill.icon = Terrain::terrain_icons[TerrainType::Foothill];
  foothill.colour = GridItem::colours[ColourType::Beige];
  Terrain foothill_terrain;
  foothill_terrain.type = TerrainType::Foothill;
  foothill_terrain.temperature = TemperatureType::Cold;
  foothill.terrain = foothill_terrain;
  return foothill;
}

GridItem Grid::generate_forest_terrain_() {
  int random_choice = rand() % 6;
  TerrainType forest_type;
  switch (random_choice) {
  case 0:
    forest_type = TerrainType::Conifer_Forest;
    break;
  case 1:
    forest_type = TerrainType::Ash_Forest;
    break;
  case 2:
    forest_type = TerrainType::Pine_Forest;
    break;
  default:
    forest_type = TerrainType::Conifer_Forest;
    break;
  }

  GridItem forest;
  forest.icon = Terrain::terrain_icons[forest_type];
  forest.colour = GridItem::colours[ColourType::Green];
  Terrain forest_terrain;
  forest_terrain.type = forest_type;
  forest_terrain.temperature = TemperatureType::Temperate;
  forest.terrain = forest_terrain;
  return forest;
}

GridItem Grid::generate_ocean_terrain_() {
  GridItem ocean;
  ocean.icon = Terrain::terrain_icons[TerrainType::Ocean];
  ocean.colour = GridItem::colours[ColourType::Blue];
  Terrain ocean_terrain;
  ocean_terrain.type = TerrainType::Ocean;
  ocean_terrain.temperature = TemperatureType::Cold;
  ocean.terrain = ocean_terrain;
  return ocean;
}

void Grid::set_colour_for_item_(GridItem item) {
  int r = item.colour.r;
  int g = item.colour.g;
  int b = item.colour.b;
  selected_colour_pair_ = item.colour.colour_pair_number;
  const int CUSTOM_COLOR = COLOR_WHITE + selected_colour_pair_;

  init_color(CUSTOM_COLOR, r, g, b);
  init_pair(selected_colour_pair_, CUSTOM_COLOR, COLOR_BLACK);

  attron(COLOR_PAIR(selected_colour_pair_));
}

void Grid::unset_colour_() {
  attroff(COLOR_PAIR(selected_colour_pair_));
  selected_colour_pair_ = 1;
}
