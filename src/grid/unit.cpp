#include "../include/unit.hpp"
#include <random>

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

Unit::Unit() {
  // Completely random unit
  int random_choice = rand() % Unit::unit_templates.size();
  // TODO: generate a random name according to race type.
  *this = Unit::unit_templates[random_choice];
}

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