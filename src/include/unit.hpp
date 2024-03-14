#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "history.hpp"
#include "item.hpp"

enum class RaceType {
  Human,
  Dwarf,
  Elf,
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
  Gelatinid,
};

struct Unit {
  static std::vector<Unit> unit_templates;
  static Unit get_random_good_unit();
  static Unit get_random_lesser_evil_unit();

  Unit();
  Unit(RaceType race);
  Unit(std::string name, std::optional<Weapon> weapon,
       std::optional<Armour> armour, std::vector<Item> loot, History history,
       int health, RaceType race);

  Unit(const Unit &obj);
  Unit &operator=(const Unit &obj);

  std::string name;
  std::optional<Weapon> weapon;
  std::optional<Armour> armour;
  std::vector<Item> loot;
  History history;
  int health;
  RaceType race;
};