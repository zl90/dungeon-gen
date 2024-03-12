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
  Trolls_Den
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

  static std::unordered_map<StructureType, const wchar_t *> structure_icons;
  static std::unordered_map<StructureType, std::string> structure_names;
  static std::string get_random_name(StructureType, StructureStatusType);

  std::string name;
  StructureType type;
  StructureStatusType status;
  std::optional<Unit> owner;
};