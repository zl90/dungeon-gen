#pragma once
#include <vector>

class HeatMap {
public:
  HeatMap(unsigned int x, unsigned int y);

private:
  std::vector<std::vector<float>> heatmap;
};
