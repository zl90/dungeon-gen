#include "../include/unit.hpp"
#include <algorithm>
#include <exception>
#include <random>
#include <stdexcept>

std::vector<Unit> Unit::unit_templates = {
    {"", Weapon{}, Armour{}, {}, History{}, 100, RaceType::Human},
    {"", Weapon{}, Armour{}, {}, History{}, 140, RaceType::Dwarf},
    {"", Weapon{}, Armour{}, {}, History{}, 100, RaceType::Elf},
    {"", Weapon{}, Armour{}, {}, History{}, 40, RaceType::Goblin},
    {"", Weapon{}, Armour{}, {}, History{}, 180, RaceType::Orc},
    {"", Weapon{}, Armour{}, {}, History{}, 400, RaceType::Ogre},
    {"", Weapon{}, Armour{}, {}, History{}, 1000, RaceType::Troll},
    {"", Weapon{}, Armour{}, {}, History{}, 80, RaceType::Arachnid},
    {"", Weapon{}, Armour{}, {}, History{}, 100, RaceType::ToadMan},
    {"", Weapon{}, Armour{}, {}, History{}, 20, RaceType::Fairy},
    {"", Weapon{}, Armour{}, {}, History{}, 5000, RaceType::Dragon},
    {"", Weapon{}, Armour{}, {}, History{}, 80, RaceType::Undead},
    {"", Weapon{}, Armour{}, {}, History{}, 100, RaceType::Gnome},
    {"", Weapon{}, Armour{}, {}, History{}, 70, RaceType::Nymph},
    {"", Weapon{}, Armour{}, {}, History{}, 10, RaceType::Spirit},
    {"", Weapon{}, Armour{}, {}, History{}, 80, RaceType::Gelatinid},
};

Unit Unit::get_random_good_unit() {
  int random_choice = rand() % 3;
  RaceType race_type;

  switch (random_choice) {
  case 0:
    race_type = RaceType::Human;
    break;
  case 1:
    race_type = RaceType::Dwarf;
    break;
  case 2:
    race_type = RaceType::Elf;
    break;
  default:
    race_type = RaceType::Human;
    break;
  }

  Unit unit(race_type);
  return unit;
}

Unit Unit::get_random_lesser_evil_unit() {
  int random_choice = rand() % 5;
  RaceType race_type;

  switch (random_choice) {
  case 0:
    race_type = RaceType::Goblin;
    break;
  case 1:
    race_type = RaceType::Orc;
    break;
  case 2:
    race_type = RaceType::Arachnid;
    break;
  case 3:
    race_type = RaceType::Undead;
    break;
  case 4:
    race_type = RaceType::Ogre;
    break;
  default:
    race_type = RaceType::Goblin;
    break;
  }

  Unit unit(race_type);
  return unit;
}

Unit::Unit() {
  // Completely random unit
  int random_choice = rand() % Unit::unit_templates.size();
  // TODO: generate a random name according to race type.
  *this = Unit::unit_templates[random_choice];
}

Unit::Unit(RaceType type) {
  auto it =
      std::find_if(unit_templates.begin(), unit_templates.end(),
                   [type](const Unit &unit) { return unit.race == type; });

  if (it != unit_templates.end()) {
    *this = *it;
  } else {
    throw std::runtime_error("Unit not found for RaceType");
  }
};

Unit::Unit(std::string name, std::optional<Weapon> weapon,
           std::optional<Armour> armour, std::vector<Item> loot,
           History history, int health, RaceType race)
    : name(name), weapon(weapon), armour(armour), loot(loot), history(history),
      health(health), race(race){};

Unit::Unit(const Unit &obj) {
  this->name = obj.name;
  this->weapon = obj.weapon;
  this->armour = obj.armour;
  this->loot = obj.loot;
  this->history = obj.history;
  this->health = obj.health;
  this->race = obj.race;
};

Unit &Unit::operator=(const Unit &other) {
  if (this != &other) {
    name = other.name;
    weapon = other.weapon;
    armour = other.armour;
    loot = other.loot;
    history = other.history;
    health = other.health;
    race = other.race;
  }
  return *this;
}