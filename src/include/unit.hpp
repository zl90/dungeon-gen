#pragma once

#include <string>
#include <vector>

#include "history.hpp"
#include "item.hpp"

enum class RaceType {
  Human,
  Dwarf,
  Goblin,
  Orc,
  Ogre,
  Troll,
  Arachnid,
  ToadMan,
  Fairy,
  Dragon,
  Undead,
  Gnome,
  Nymph,
  Spirit,
  Gelatinid
};

struct Unit {
  std::string name;
  Weapon weapon;
  Armour armour;
  std::vector<Item> loot;
  History history;
  int health;
  RaceType type;
};