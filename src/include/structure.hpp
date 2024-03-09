#pragma once
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
  MageTower,
  Library
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
  static std::unordered_map<StructureType, const wchar_t *> structure_icons;

  std::string name;
  StructureType type;
  StructureStatusType status;
};