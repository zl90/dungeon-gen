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