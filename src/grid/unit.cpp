#include "../include/unit.hpp"
#include <algorithm>
#include <exception>
#include <random>
#include <stdexcept>
#include <unordered_map>

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

std::unordered_map<RaceType, std::string> Unit::race_names = {
    {RaceType::Human, "Human"},     {RaceType::Dwarf, "Dwarf"},
    {RaceType::Elf, "Elf"},         {RaceType::Goblin, "Goblin"},
    {RaceType::Orc, "Orc"},         {RaceType::Ogre, "Ogre"},
    {RaceType::Troll, "Troll"},     {RaceType::Arachnid, "Arachnid"},
    {RaceType::ToadMan, "ToadMan"}, {RaceType::Fairy, "Fairy"},
    {RaceType::Dragon, "Dragon"},   {RaceType::Undead, "Undead"},
    {RaceType::Gnome, "Gnome"},     {RaceType::Nymph, "Nymph"},
    {RaceType::Spirit, "Spirit"},   {RaceType::Gelatinid, "Gelatinid"},
};

std::unordered_map<RaceType, std::string> Unit::structure_race_names = {
    {RaceType::Human, "Human"},     {RaceType::Dwarf, "Dwarvish"},
    {RaceType::Elf, "Elvish"},      {RaceType::Goblin, "Goblin"},
    {RaceType::Orc, "Orcish"},      {RaceType::Ogre, "Ogre"},
    {RaceType::Troll, "Troll"},     {RaceType::Arachnid, "Arachnid"},
    {RaceType::ToadMan, "ToadMan"}, {RaceType::Fairy, "Fairy"},
    {RaceType::Dragon, "Dragon"},   {RaceType::Undead, "Undead"},
    {RaceType::Gnome, "Gnomish"},   {RaceType::Nymph, "Nymph"},
    {RaceType::Spirit, "Spirit"},   {RaceType::Gelatinid, "Gelatinid"},
};

std::unordered_map<RaceType, std::vector<std::string>>
    Unit::random_name_prefixes_by_race = {
        {RaceType::Elf,
         {"Ald", "El", "Gal", "Thal", "Mer", "Var", "Zan", "Mor", "Ili", "Aer",
          "Mal", "Moel", "Fel", "Fal", "Fen", "Fin", "Fini"}},
        {RaceType::Dwarf,
         {"Dur", "Thra", "Bal", "Thro", "Gim", "Oin", "Gloin", "Thorin",
          "Balin", "Dwalin", "Fili", "Kili", "Bifur", "Bofur", "Bombur", "Dori",
          "Nori", "Ori"}},
        {RaceType::Human, {"Ad",  "Ald", "And", "Bal", "Bran", "Cor", "Dar",
                           "Eld", "Fal", "Gar", "Hal", "Ing",  "Kor", "Lan",
                           "Mar", "Nar", "Oth", "Pal", "Quar", "Ral", "Sar",
                           "Tar", "Uth", "Val", "Wil", "Xan",  "Yar", "Zan"}},
        {RaceType::Goblin,
         {"Gor", "Dak", "Gul", "Kor", "Nar", "Ruk", "Snag", "Thro", "Ug", "Yag",
          "Zog", "Mog", "Grik", "Krik", "Nok", "Nog", "Drog", "Bog", "Brog"}},
        {RaceType::Orc,
         {"Gor", "Dak", "Gul", "Kor", "Nar", "Ruk", "Snag", "Thro", "Ug", "Yag",
          "Zog", "Mog", "Grik", "Krik", "Nok", "Nog", "Drog", "Bog", "Brog"}},
        {RaceType::Ogre,
         {"Gor", "Dak", "Gul", "Kor", "Nar", "Ruk", "Snag", "Thro", "Ug", "Yag",
          "Zog", "Mog", "Grik", "Krik", "Nok", "Nog", "Drog", "Bog", "Brog"}},
        {RaceType::Troll,
         {"Gor", "Dak", "Gul", "Kor", "Nar", "Ruk", "Snag", "Thro", "Ug", "Yag",
          "Zog", "Mog", "Grik", "Krik", "Nok", "Nog", "Drog", "Bog", "Brog"}},
        {RaceType::Arachnid,
         {"Silk", "Venom", "Web", "Fang", "Spinner", "Leg", "Crawler",
          "Scuttle", "Thread", "Trap", "Toxin", "Hairy", "Skitter", "Creep",
          "Lurk", "Weave", "Pincer", "Grip", "Stalker"}},
        {RaceType::ToadMan,
         {"Bufo",       "Crapo",         "Hyla",         "Rana",
          "Sapo",       "Atelopus",      "Duttaphrynus", "Pelobates",
          "Scaphiopus", "Xenopus",       "Agalychnis",   "Phyllomedusa",
          "Alytes",     "Bombina",       "Bufotes",      "Bufo",
          "Epidalea",   "Ingerophrynus", "Natterjack",   "Pedostibes",
          "Pelophylax", "Rhaebo",        "True Toads"}},
        {RaceType::Fairy,
         {"Aur", "Cele", "Ellyl", "Fay", "Lla", "Myr", "Nim", "Ond", "Pix",
          "Sidhe", "Tam", "Tylwyth", "Uisge", "Wend", "Will", "Ylva", "Za",
          "Zephyr"}},
        {RaceType::Dragon,
         {"Aur", "Cy", "Draco", "Fafnir", "Hydra", "Ladon", "Nidhogg", "Pyro",
          "Ryuu", "Tatsu", "Wyrm", "Zmey", "Vasuki", "Jormungandr",
          "Midgardsormr"}},
        {RaceType::Undead,
         {"Apo", "Necro", "Reven", "Spectro", "Wight", "Zombi", "Liche",
          "Ghoul", "Polter", "Vamp", "Skel", "Mum", "Gast", "Shade", "Wraith",
          "Phant"}},
        {RaceType::Gnome,
         {"Alb", "Barb", "Dig", "Fos", "Gnarl", "Hob", "Ill", "Knick", "Knurl",
          "Min", "Nock", "Pebbl", "Rack", "Rip", "Scratch", "Thim", "Weld"}},
        {RaceType::Nymph,
         {"Aqua", "Drya", "Eco", "Flor", "Hali", "Limna", "Meli", "Nai", "Orea",
          "Peg", "Styra", "Undi", "Xylo", "Zeph"}},
        {RaceType::Spirit,
         {"Anima", "Ecto", "Eth", "Manes", "Phasm", "Spectra", "Spirit",
          "Specter", "Soul", "Wraith", "Appar", "Shad", "Phant"}},
        {RaceType::Gelatinid,
         {"Gel", "Glo", "Slime", "Muc", "Ooze", "Jell", "Slop", "Glop", "Gunk",
          "Blob", "Mire", "Gelatin", "Gelid", "Squelch", "Visc"}}};

std::unordered_map<RaceType, std::vector<std::string>>
    Unit::random_name_suffixes_by_race = {
        {RaceType::Elf,
         {"dor", "orin", "wyn", "vyn", "dil", "wynn", "nor", "droth", "kor",
          "kon", "korn"}},
        {RaceType::Dwarf,
         {"in",   "or",   "an",   "ur",    "rin", "run", "rim", "rum",
          "grim", "grin", "thor", "thrin", "gar", "gur", "lin", "lum",
          "dir",  "dur",  "nar",  "nur",   "bur", "bor", "mir", "mur"}},
        {RaceType::Human,
         {"dor", "orin", "wyn", "vyn", "dil", "wynn", "nor", "droth", "kor",
          "kon", "korn"}},
        {RaceType::Goblin,
         {"gob", "ob", "nob", "gobin", "nobin", "snob", "gobbin", "dob", "lob",
          "nub", "rub", "grub", "kob", "lob", "slob", "blob"}},
        {RaceType::Orc,
         {"gob", "ob", "nob", "gobin", "nobin", "snob", "gobbin", "dob", "lob",
          "nub", "rub", "grub", "kob", "lob", "slob", "blob"}},
        {RaceType::Ogre,
         {"gob", "ob", "nob", "gobin", "nobin", "snob", "gobbin", "dob", "lob",
          "nub", "rub", "grub", "kob", "lob", "slob", "blob"}},
        {RaceType::Troll,
         {"gob", "ob", "nob", "gobin", "nobin", "snob", "gobbin", "dob", "lob",
          "nub", "rub", "grub", "kob", "lob", "slob", "blob"}},
        {RaceType::Arachnid,
         {"web", "spin", "leg", "fang", "thread", "toxin", "trap", "venom",
          "bite", "silk", "weaver", "stalker", "pincer", "fang", "grip"}},
        {RaceType::ToadMan,
         {"croak", "hopper",  "ribbit",  "wart",   "jumper", "tongue",
          "spawn", "slime",   "swimmer", "leaper", "toad",   "bulge",
          "muck",  "croaker", "hopple",  "paddle", "belch",  "tumbler",
          "gulp",  "darter",  "cropper"}},
        {RaceType::Fairy,
         {"belle", "dust",   "gleam",   "jinx",     "kiss", "lily", "mirth",
          "nymph", "pebble", "quest",   "rune",     "song", "tale", "whisper",
          "yarn",  "zephyr", "glimmer", "gossamer", "hush", "lilt"}},
        {RaceType::Dragon,
         {"scale", "fire",  "claw",  "wing",   "breath", "flame", "fury",
          "swoop", "tail",  "eye",   "scales", "fang",   "crest", "hide",
          "roar",  "shard", "spike", "storm",  "thrall", "wrath"}},
        {RaceType::Undead,
         {"bone",  "wraith", "soul",    "shade",  "ghost",  "ghoul", "tomb",
          "crypt", "grave",  "specter", "spirit", "curse",  "rot",   "death",
          "bloom", "flesh",  "dread",   "decay",  "shroud", "haunt"}},
        {RaceType::Gnome,
         {"glimmer", "gear",    "knob",   "widget",  "sprocket",
          "cog",     "whistle", "gadget", "tinker",  "clank",
          "smudge",  "wrench",  "sprig",  "crank",   "twist",
          "lever",   "ratchet", "screw",  "spindle", "spring"}},
        {RaceType::Nymph,
         {"bloom",  "dew",   "flower", "glen",   "harp",  "lark", "maiden",
          "nymph",  "quill", "rose",   "shade",  "thorn", "veil", "whisper",
          "willow", "fawn",  "brook",  "ripple", "echo",  "lily"}},
        {RaceType::Spirit,
         {"soul",  "essence",  "whisper",  "shade",      "wraith",
          "ghost", "specter",  "phantom",  "apparition", "ether",
          "aura",  "manifest", "presence", "echo",       "spirit",
          "wisp",  "shroud",   "veil",     "flicker",    "glow"}},
        {RaceType::Gelatinid,
         {"gel",  "ooze",  "muck",   "slime",  "glop",  "gunk",    "sludge",
          "goo",  "jelly", "slop",   "glop",   "gloop", "squelch", "plop",
          "plop", "mire",  "jiggle", "squish", "drip",  "drop"}}};

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
  *this = Unit::unit_templates[random_choice];
  name = GetRandomName();
}

Unit::Unit(RaceType type) {
  auto it =
      std::find_if(unit_templates.begin(), unit_templates.end(),
                   [type](const Unit &unit) { return unit.race == type; });

  if (it != unit_templates.end()) {
    *this = *it;
    name = GetRandomName();
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

auto Unit::GetRandomName() -> std::string {
  std::vector<std::string> prefixes = Unit::random_name_prefixes_by_race[race];
  std::vector<std::string> suffixes = Unit::random_name_suffixes_by_race[race];

  return prefixes[rand() % prefixes.size()] +
         suffixes[rand() % suffixes.size()];
}