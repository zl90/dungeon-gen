#pragma once

#include <string>
#include <vector>

#include "history.hpp"

enum class WeaponType {
  Sword,
  GreatSword,
  Wand,
  Staff,
  Axe,
  GreatAxe,
};

enum class ArmourType { BreastPlate, LegPlates, Shield, Helm, Ring, Boots };

enum class ArtifactType { Tome, Relic, Trinket };

struct Item {
  History history;
  std::string name;
};

struct Weapon : Item {
  int damage;
  WeaponType type;
};

struct Armour : Item {
  int armour;
  ArmourType type;
};

struct Potion : Item {
  int healing;
};

struct Gold : Item {
  int value;
};

struct Artifact : Item {};