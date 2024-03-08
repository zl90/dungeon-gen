#pragma once
#include <string>

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
  std::string name;
  StructureType type;
  StructureStatusType status;
};