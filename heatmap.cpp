#include "heatmap.h"
#include <random>

HeatMap::HeatMap(unsigned int x, unsigned int y) {
  double max_number_of_hotspots = rand() % x / 10;
  double hotspot_probability = (x * y) / max_number_of_hotspots;

  for (unsigned int i = 0; i < x; i++) {
    for (unsigned int j = 0; j < y; j++) {
      heatmap[i][j] = 0.0;

      if (rand() % (x * y) < hotspot_probability) {
        heatmap[i][j] = 1.0;
      }
    }
  }
}
