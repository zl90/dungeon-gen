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

  for (int k = 0; k < 10; k++) {
    // Perform convolution 10 times to smooth the heatmap
    for (unsigned int i = 0; i < x; i++) {
      for (unsigned int j = 0; j < y; j++) {
        if (i == 0 && j == 0) {
          // top left corner
        } else if (i == x - 1 && j == 0) {
          // top right corner
        } else if (i == 0 && j == y - 1) {
          // bottom left corner
        } else if (i == x - 1 && j == y - 1) {
          // bottom right corner
        } else if (i == 0) {
          // leftmost column
        } else if (i == x - 1) {
          // rightmost column
        } else if (j == 0) {
          // top row
        } else if (j == y - 1) {
          // bottom row
        } else [[likely]] {
          // normal convolution
        }
      }
    }
  }
}
