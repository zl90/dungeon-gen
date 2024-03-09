#pragma once

#include <string>
#include <vector>
#include <wchar.h>

#include "history.hpp"
#include "item.hpp"
#include "structure.hpp"
#include "terrain.hpp"
#include "unit.hpp"

enum class ColourType {
  Blue,
  Light_Blue,
  Red,
  Pink,
  Purple,
  Orange,
  Yellow,
  Green,
  Light_Green,
  White,
  Grey,
  Beige,
  Brown,
  Light_Pink
};

struct Colour {
  int r;
  int g;
  int b;
  int colour_pair_number;

  Colour &operator=(const Colour &obj) {
    r = obj.r;
    g = obj.g;
    b = obj.b;
    colour_pair_number = obj.colour_pair_number;

    return *this;
  }
};

struct GridItem {
  static std::unordered_map<ColourType, Colour> colours;

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
  Colour colour;
};