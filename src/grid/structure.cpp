#include "../include/structure.hpp"

std::unordered_map<StructureType, const wchar_t *> Structure::structure_icons =
    {
        {StructureType::Ruins, L"╨"},      {StructureType::Temple, L"π"},
        {StructureType::Settlement, L"î"}, {StructureType::Fortress, L"Ω"},
        {StructureType::Inn, L"±"},        {StructureType::Cave, L"◘"},
        {StructureType::Grave, L"▬"},      {StructureType::Boneyard, L"º"},
        {StructureType::Cemetery, L"≡"},   {StructureType::Bridge, L"╦"},
        {StructureType::Mage_Tower, L"╥"}, {StructureType::Library, L"µ"},
        {StructureType::Trolls_Den, L"ô"}, {StructureType::Pit, L"º"},
};

std::unordered_map<StructureType, std::string> Structure::structure_names = {
    {StructureType::Ruins, "Ruins"},
    {StructureType::Temple, "Temple"},
    {StructureType::Settlement, "Settlement"},
    {StructureType::Fortress, "Fortress"},
    {StructureType::Inn, "Inn"},
    {StructureType::Cave, "Cave"},
    {StructureType::Grave, "Grave"},
    {StructureType::Boneyard, "Boneyard"},
    {StructureType::Cemetery, "Cemetery"},
    {StructureType::Bridge, "Bridge"},
    {StructureType::Mage_Tower, "Mage Tower"},
    {StructureType::Library, "Library"},
    {StructureType::Pit, "Pit"},
    {StructureType::Trolls_Den, "Troll Den"},
};

Structure::Structure(StructureType type) {
  StructureStatusType status = StructureStatusType::Abandoned;
  this->type = type;
  this->status = status;
  this->name = Structure::GetRandomName(type, status);
}

Structure::Structure(StructureType type, StructureStatusType status) {
  this->type = type;
  this->status = status;
  this->name = Structure::GetRandomName(type, status);
}

Structure::Structure(StructureType type, StructureStatusType status,
                     Unit owner) {
  this->type = type;
  this->status = status;
  this->owner = owner;
  this->name = Structure::GetRandomName(type, status);
}

std::vector<std::string> Structure::random_name_prefixes = {
    "Ald",  "El",   "Gal",  "Thal", "Mer",  "Var",  "Zan",  "Mel",   "Mor",
    "Ae",   "Ala",  "Cel",  "Eld",  "Elen", "Lind", "Myth", "Tir",   "Vor",
    "Ili",  "Aer",  "Mal",  "Moel", "Fel",  "Fal",  "Fen",  "Fin",   "Fini",
    "Bal",  "Dur",  "Fel",  "Gim",  "Kil",  "Thor", "Thra", "Borad", "Ilmil",
    "Bar",  "Ea",   "Gal",  "Har",  "Mar",  "Rad",  "Tar",  "Val",   "Wil",
    "Bog",  "Gob",  "Mog",  "Nag",  "Rok",  "Snag", "Ug",   "Yag",   "Zog",
    "Drog", "Gor",  "Gul",  "Kor",  "Nar",  "Ruk",  "Thro", "Yag",   "Zog",
    "Aur",  "Cele", "Elly", "Fay",  "Lla",  "Myr",  "Nim",  "Ond",   "Pix"};
std::vector<std::string> Structure::random_name_suffixes = {
    "dor",    "orin",   "wyn",  "vyn",   "dil",    "wynn",   "nor",
    "droth",  "kor",    "kon",  "korn",  "ath",    "dor",    "el",
    "en",     "ion",    "or",   "uil",   "yr",     "glen",   "ak",
    "din",    "gar",    "grim", "in",    "lin",    "rak",    "thor",
    "dale",   "ford",   "hold", "mere",  "ridge",  "stead",  "watch",
    "digger", "hammer", "pick", "smith", "tinker", "whistle"};

std::unordered_map<RaceType, std::vector<std::string>>
    Structure::random_name_prefixes_by_race_for_structure = {
        {RaceType::Elf,
         {"Ae", "Ala", "Cel", "Eld", "Elen", "Lind", "Myth", "Tir", "Vor"}},
        {RaceType::Dwarf,
         {"Bal",   "Dur",   "Fel",   "Gim",   "Kil", "Thor",  "Thra",
          "Borad", "Ilmil", "Barad", "Balud", "Mor", "Bolud", "Bura",
          "Burad", "Din",   "Dim",   "Dum",   "Dom", "Ruud"}},
        {RaceType::Human,
         {"Bar", "Ea", "Gal", "Har", "Mar", "Rad", "Tar", "Val", "Wil"}},
        {RaceType::Goblin,
         {"Bog", "Gob", "Mog", "Nag", "Rok", "Snag", "Ug", "Yag", "Zog"}},
        {RaceType::Orc,
         {"Drog", "Gor", "Gul", "Kor", "Nar", "Ruk", "Thro", "Yag", "Zog"}},
        {RaceType::Ogre,
         {"Brog", "Dug", "Gor", "Mog", "Nog", "Rog", "Throg", "Ug", "Yog"}},
        {RaceType::Troll,
         {"Brog", "Gor", "Krog", "Mog", "Nog", "Rog", "Throg", "Ug", "Yog"}},
        {RaceType::Arachnid,
         {"Fang", "Spinner", "Web", "Silk", "Leg", "Crawler", "Thread",
          "Trap"}},
        {RaceType::ToadMan,
         {"Bufo", "Crapo", "Hyla", "Rana", "Sapo", "Atelo", "Dutta", "Scaphi",
          "Xeno"}},
        {RaceType::Fairy,
         {"Aur", "Cele", "Elly", "Fay", "Lla", "Myr", "Nim", "Ond", "Pix"}},
        {RaceType::Dragon,
         {"Aur", "Cy", "Draco", "Fafnir", "Hydra", "Ladon", "Nidhogg", "Pyro"}},
        {RaceType::Undead,
         {"Apo", "Necro", "Reven", "Spectro", "Wight", "Zombi", "Liche"}},
        {RaceType::Gnome,
         {"Alb", "Barb", "Dig", "Fos", "Gnarl", "Hob", "Ill", "Knick",
          "Knurl"}},
        {RaceType::Nymph,
         {"Aqua", "Drya", "Eco", "Flor", "Hali", "Limna", "Meli", "Nai",
          "Orea"}},
        {RaceType::Spirit,
         {"Anima", "Ecto", "Eth", "Manes", "Phasm", "Spectra", "Spirit"}},
        {RaceType::Gelatinid,
         {"Gel", "Glo", "Slime", "Muc", "Ooze", "Jell", "Slop", "Glop",
          "Gunk"}}};

std::unordered_map<RaceType, std::vector<std::string>>
    Structure::random_name_suffixes_by_race_for_structure = {
        {RaceType::Elf,
         {"ath", "dor", "el", "en", "ion", "or", "uil", "yr", "glen"}},
        {RaceType::Dwarf,
         {"ak", "din", "gar", "grim", "in", "lin", "rak", "thor", "un", "din",
          "dun", "ia"}},
        {RaceType::Human,
         {"dale", "ford", "hold", "mere", "ridge", "stead", "watch"}},
        {RaceType::Goblin,
         {"fang", "gob", "grub", "muck", "snag", "stink", "toe", "wretch"}},
        {RaceType::Orc,
         {"bash", "fang", "gore", "krash", "smash", "tusk", "warg"}},
        {RaceType::Ogre,
         {"bash", "crush", "gore", "mash", "smash", "thud", "tusk"}},
        {RaceType::Troll,
         {"bash", "crush", "grub", "smash", "stomp", "thud", "tusk"}},
        {RaceType::Arachnid,
         {"web", "spinner", "fang", "leg", "thread", "silk", "trap"}},
        {RaceType::ToadMan,
         {"hop", "leap", "jump", "wade", "gulp", "croak", "belch"}},
        {RaceType::Fairy,
         {"blossom", "glimmer", "shimmer", "whisper", "twinkle", "dew"}},
        {RaceType::Dragon,
         {"flame", "fire", "scale", "claw", "wing", "breath", "roar"}},
        {RaceType::Undead,
         {"shade", "wraith", "specter", "ghost", "haunt", "bone", "crypt"}},
        {RaceType::Gnome,
         {"digger", "hammer", "pick", "smith", "tinker", "whistle"}},
        {RaceType::Nymph,
         {"brook", "dew", "lake", "spring", "stream", "water"}},
        {RaceType::Spirit,
         {"essence", "shade", "wraith", "ghost", "specter", "soul"}},
        {RaceType::Gelatinid,
         {"goo", "slime", "muck", "ooze", "glop", "jelly", "slop"}}};

std::string Structure::GetRandomName(StructureType type,
                                     StructureStatusType status) {
  std::string output;
  if (owner.has_value()) {
    std::vector<std::string> prefixes =
        Unit::random_name_prefixes_by_race[owner->race];
    std::vector<std::string> suffixes =
        Unit::random_name_suffixes_by_race[owner->race];

    output += Unit::structure_race_names[owner->race] + " ";
    output += Structure::structure_names[type];
    output += " of ";
    output +=
        prefixes[rand() % prefixes.size()] + suffixes[rand() % suffixes.size()];

    return output;
  } else {
    output += Structure::structure_names[type];
    output += " of ";

    int random_choice = rand() % random_name_prefixes.size();
    output += random_name_prefixes[random_choice];
    random_choice = rand() % random_name_suffixes.size();
    output += random_name_suffixes[random_choice];

    return output;
  }
}