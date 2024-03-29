#pragma once

#include <string>
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
  static std::unordered_map<TerrainType, std::string> terrain_names;
  static std::unordered_map<TemperatureType, std::string> temperature_names;

  TerrainType type;
  TemperatureType temperature;
};