#pragma once

#include <string>
#include <vector>

struct LogEntry {
  int year;
  std::string entry;
};

struct History {
  std::vector<LogEntry> entries;
};