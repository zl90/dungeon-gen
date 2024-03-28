#pragma once
#include "unit.hpp"
#include <optional>
#include <string>
#include <unordered_map>
#include <wchar.h>

enum class StructureType {
  Ruins,
  Temple,
  Settlement,
  Fortress,
  Inn,
  Cave,
  Grave,
  Boneyard,
  Cemetery,
  Bridge,
  Mage_Tower,
  Library,
  Trolls_Den,
  Pit
};

enum class StructureStatusType {
  Hallowed,
  Blessed,
  Cursed,
  Abandoned,
  Consecrated,
  Hidden,
  Collapsed,
  New
};

struct Structure {
  Structure(StructureType type);
  Structure(StructureType type, StructureStatusType status);
  Structure(StructureType type, StructureStatusType status, Unit owner);

  static std::unordered_map<StructureType, const wchar_t *> structure_icons;
  static std::unordered_map<StructureType, std::string> structure_names;
  static std::unordered_map<RaceType, std::vector<std::string>>
      random_name_prefixes_by_race_for_structure;
  static std::unordered_map<RaceType, std::vector<std::string>>
      random_name_suffixes_by_race_for_structure;
  static std::vector<std::string> random_name_prefixes;
  static std::vector<std::string> random_name_suffixes;

  auto GetRandomName(StructureType, StructureStatusType) -> std::string;

  std::string name;
  StructureType type;
  StructureStatusType status;
  std::optional<Unit> owner;
};