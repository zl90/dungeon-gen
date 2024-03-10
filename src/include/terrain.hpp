#pragma once

#include <unordered_map>
#include <wchar.h>

enum class TerrainType {
  Conifer_Forest,
  Ash_Forest,
  Pine_Forest,
  Grassy_Plains,
  Chaparral,
  Mountain,
  Foothill,
  Frozen_Tundra,
  Barren_Plains,
  Volcanic_Wasteland,
  Sandy_Desert,
  Ocean
};

enum class TemperatureType {
  Temperate,
  Hot,
  Humid,
  Cold,
  Frigid,
};

struct Terrain {
  static std::unordered_map<TerrainType, const wchar_t *> terrain_icons;

  TerrainType type;
  TemperatureType temperature;
};