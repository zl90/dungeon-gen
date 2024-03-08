#pragma once

#include <string>
#include <vector>

#include "history.hpp"
#include "item.hpp"

struct Unit {
  std::string name;
  Weapon weapon;
  Armour armour;
  std::vector<Item> loot;
  History history;
  int health;
};