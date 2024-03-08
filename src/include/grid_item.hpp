#pragma once

#include <string>
#include <vector>

#include "history.hpp"
#include "item.hpp"
#include "structure.hpp"
#include "terrain.hpp"

class GridItem {
public:
  Terrain terrain;

  Structure structure;

  /** Contains logs for events that occurred on this structure in the past. */
  History history;

  std::vector<Item> items;

private:
};