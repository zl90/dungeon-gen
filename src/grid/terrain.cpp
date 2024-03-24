#include "../include/terrain.hpp"

std::unordered_map<TerrainType, const wchar_t *> Terrain::terrain_icons = {
    {TerrainType::Mountain, L"▲"},
    {TerrainType::Foothill, L"⌂"},
    {TerrainType::Conifer_Forest, L"↑"},
    {TerrainType::Ash_Forest, L"⌠"},
    {TerrainType::Pine_Forest, L"n"},
    {TerrainType::Grassy_Plains, L"\""},
    {TerrainType::Frozen_Tundra, L"*"},
    {TerrainType::Barren_Plains, L"ⁿ"},
    {TerrainType::Volcanic_Wasteland, L"▴"},
    {TerrainType::Sandy_Desert, L"∩"},
    {TerrainType::Chaparral, L"ⁿ"},
    {TerrainType::Ocean, L"≈"},
};

std::unordered_map<TerrainType, std::string> Terrain::terrain_names = {
    {TerrainType::Mountain, "Mountain"},
    {TerrainType::Foothill, "Foothills"},
    {TerrainType::Conifer_Forest, "Conifer Forest"},
    {TerrainType::Ash_Forest, "Ash Forest"},
    {TerrainType::Pine_Forest, "Pine Forest"},
    {TerrainType::Grassy_Plains, "Grassy Plains"},
    {TerrainType::Frozen_Tundra, "Frozen Tundra"},
    {TerrainType::Barren_Plains, "Barren Plains"},
    {TerrainType::Volcanic_Wasteland, "Volcanic Wasteland"},
    {TerrainType::Sandy_Desert, "Sandy Desert"},
    {TerrainType::Chaparral, "Chaparral"},
    {TerrainType::Ocean, "Ocean"},
};