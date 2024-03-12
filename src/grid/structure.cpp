#include "../include/structure.hpp"
#include <iostream>

std::unordered_map<StructureType, const wchar_t *> Structure::structure_icons =
    {
        {StructureType::Ruins, L"Θ"},      {StructureType::Temple, L"π"},
        {StructureType::Settlement, L"î"}, {StructureType::Fortress, L"Ω"},
        {StructureType::Inn, L"±"},        {StructureType::Cave, L"◘"},
        {StructureType::Grave, L"▬"},      {StructureType::Boneyard, L"º"},
        {StructureType::Cemetery, L"≡"},   {StructureType::Bridge, L"╦"},
        {StructureType::Mage_Tower, L"╥"}, {StructureType::Library, L"Θ"},
};

std::unordered_map<StructureType, std::string> Structure::structure_names = {
    {StructureType::Ruins, "Ruins"},
    {StructureType::Temple, "Temple"},
    {StructureType::Settlement, "Settlement"},
    {StructureType::Fortress, "Fortress"},
    {StructureType::Inn, "Inn"},
    {StructureType::Cave, "Cave"},
    {StructureType::Grave, "Grave"},
    {StructureType::Boneyard, "Boneyard"},
    {StructureType::Cemetery, "Cemetery"},
    {StructureType::Bridge, "Bridge"},
    {StructureType::Mage_Tower, "Mage Tower"},
    {StructureType::Library, "Library"},
};

Structure::Structure(StructureType type) {
  StructureStatusType status = StructureStatusType::Abandoned;
  this->type = type;
  this->status = status;
  this->name = Structure::get_random_name(type, status);
}

Structure::Structure(StructureType type, StructureStatusType status) {
  this->type = type;
  this->status = status;
  this->name = Structure::get_random_name(type, status);
}

std::vector<std::string> random_name_prefixes = {
    "Ald", "El",  "Gal", "Thal", "Mer", "Var", "Zan", "Mel", "Mor",
    "Ili", "Aer", "Mal", "Moel", "Fel", "Fal", "Fen", "Fin", "Fini"};
std::vector<std::string> random_name_suffixes = {"dor", "orin", "wyn", "vyn",
                                                 "dil", "wynn", "nor", "droth",
                                                 "kor", "kon",  "korn"};

std::string Structure::get_random_name(StructureType type,
                                       StructureStatusType status) {
  // @TODO: improve random name generation.
  // Use the status in the name. Add random accents. Possibly keep lists of
  // existing structures to prevent duplicate names?
  std::string output;
  output += Structure::structure_names[type];
  output += " of ";

  int random_choice = rand() % random_name_prefixes.size();
  output += random_name_prefixes[random_choice];
  random_choice = rand() % random_name_suffixes.size();
  output += random_name_suffixes[random_choice];

  return output;
}