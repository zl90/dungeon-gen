#pragma once
#include <cstdint>
#include <optional>
#include <thread>
#include <unordered_map>
#include <vector>

#include "cursor.hpp"
#include "grid_item.hpp"
#include "heatmap.hpp"

class Grid {
 public:
  Grid(unsigned int width, unsigned int height);
  auto Draw() -> void;
  auto IsGameRunning() -> bool;

  auto CursorUp() -> void;
  auto CursorDown() -> void;
  auto CursorLeft() -> void;
  auto CursorRight() -> void;

 private:
  unsigned int width_;
  unsigned int height_;

  unsigned int top_offset_ = 3;

  std::vector<std::vector<GridItem>> items_;

  Cursor cursor_;

  uint8_t selected_colour_pair_ = 1;

  HeatMap terrain_heatmap_;

  bool is_game_running_ = true;

  auto MapBasicTerrain() -> void;
  auto MapDesertTerrain() -> void;
  auto MapGrassTerrain() -> void;
  auto MapFrozenTerrain() -> void;
  auto MapFortresses() -> void;
  auto MapSettlements() -> void;
  auto MapCaves() -> void;
  auto MapInns() -> void;
  auto MapBridges() -> void;
  auto MapMageTowers() -> void;
  auto MapLibraries() -> void;
  auto MapTrollsDens() -> void;
  auto MapPits() -> void;

  auto GenerateMountainTerrain() -> GridItem;
  auto GenerateFrozenTundraTerrain() -> GridItem;
  auto GenerateDesertTerrain() -> GridItem;
  auto GenerateBarrenPlainsTerrain() -> GridItem;
  auto GenerateGrassyPlainsTerrain() -> GridItem;
  auto GenerateChaparralTerrain() -> GridItem;
  auto GenerateFoothillTerrain() -> GridItem;
  auto GenerateOceanTerrain() -> GridItem;
  auto GenerateForestTerrain() -> GridItem;

  auto SetColourForItem(GridItem item, int x, int y) -> void;

  auto UnsetColour() -> void;
  auto DrawInfoPanel() -> void;
};