#pragma once

enum class TerrainType {
  Conifer_Forest,
  Ash_Forest,
  Pine_Forest,
  Grassy_Plain,
  Mountain,
  Frozen_Tundra,
  Barren_Plains,
  Volcanic_Wasteland,
};

enum class TemperatureType {
  Temperate,
  Humid,
  Cold,
  Frigid,
};

struct Terrain {
  TerrainType type;
  TemperatureType temperature;
};