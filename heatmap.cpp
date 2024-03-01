#include "heatmap.h"
#include <random>

HeatMap::HeatMap(unsigned int x, unsigned int y) {
  double max_number_of_hotspots = rand() % x / 10;
  double hotspot_probability = (x * y) / max_number_of_hotspots;

  for (unsigned int i = 0; i < x; i++) {
    for (unsigned int j = 0; j < y; j++) {
      if (rand() % (x * y) < hotspot_probability &&
          max_number_of_hotspots > 0) {
        heatmap[i][j] = 1.0;
        max_number_of_hotspots--;
      } else {
        heatmap[i][j] = 0.0;
      }
    }
  }
}
