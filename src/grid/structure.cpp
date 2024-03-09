#include "../include/structure.hpp"

std::unordered_map<StructureType, const wchar_t *> Structure::structure_icons =
    {
        {StructureType::Ruins, L"Θ"},      {StructureType::Temple, L"π"},
        {StructureType::Settlement, L"⌂"}, {StructureType::Fortress, L"Ω"},
        {StructureType::Inn, L"±"},        {StructureType::Cave, L"◘"},
        {StructureType::Grave, L"▬"},      {StructureType::Boneyard, L"º"},
        {StructureType::Cemetery, L"≡"},   {StructureType::Bridge, L"╦"},
        {StructureType::MageTower, L"╥"},  {StructureType::Library, L"Θ"},
};