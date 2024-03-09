#pragma once

#include <string>
#include <vector>
#include <wchar.h>

#include "history.hpp"
#include "item.hpp"
#include "structure.hpp"
#include "terrain.hpp"
#include "unit.hpp"

struct GridItem {
  /** The terrain of this grid tile. */
  Terrain terrain;

  /** The structure located on this grid tile. */
  Structure structure;

  /** Contains logs for events that occurred on this grid tile in the past. */
  History history;

  /** Contains all free items currently situated on this grid tile. */
  std::vector<Item> items;

  /** Contains all units currently situated on this grid tile. */
  std::vector<Unit> occupants;

  const wchar_t *icon;
};