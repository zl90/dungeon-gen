#include "heatmap.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

HeatMap::HeatMap(unsigned int x, unsigned int y) {
  width_ = x;
  height_ = y;

  float hotspot_probability = 3;

  heatmap_ = std::vector<std::vector<float>>(width_,
                                             std::vector<float>(height_, 0.0f));

  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (rand() % 100 < hotspot_probability) {
        heatmap_[i][j] = 1.0f;
      }
    }
  }

  for (int k = 0; k < 5; k++) {
    smoothen_();
  }
}

void HeatMap::print() {
  for (unsigned int j = 0; j < height_; j++) {
    for (unsigned int i = 0; i < width_; i++) {
      if (heatmap_[i][j] >= 0.7) {
        std::cout << "\033[1;31m";
      } else if (heatmap_[i][j] >= 0.5) {
        std::cout << "\033[1;33m";
      } else if (heatmap_[i][j] >= 0.2) {
        std::cout << "\033[1;32m";
      } else {
        std::cout << "\033[1;34m";
      }
      std::cout << std::fixed << std::setprecision(1) << heatmap_[i][j];
      std::cout << "\033[0m";
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

void HeatMap::smoothen_() {
  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (i == 0 && j == 0) {
        // top left corner
      } else if (i == width_ - 1 && j == 0) {
        // top right corner
      } else if (i == 0 && j == height_ - 1) {
        // bottom left corner
      } else if (i == width_ - 1 && j == height_ - 1) {
        // bottom right corner
      } else if (i == 0) {
        // leftmost column
      } else if (i == width_ - 1) {
        // rightmost column
      } else if (j == 0) {
        // top row
      } else if (j == height_ - 1) {
        // bottom row
      } else [[likely]] {
        // normal convolution
        if (heatmap_[i][j] != 1.0f) {
          float average = (heatmap_[i - 1][j + 1] + heatmap_[i][j + 1] +
                           heatmap_[i + 1][j + 1] + heatmap_[i - 1][j] +
                           heatmap_[i + 1][j] + heatmap_[i - 1][j - 1] +
                           heatmap_[i][j - 1] + heatmap_[i + 1][j - 1]) /
                          8.0f;
          float increment = average * ((rand() % 100) + 1) / 100.0f;
          heatmap_[i][j] = std::min(heatmap_[i][j] + increment, 1.0f);
        }
      }
    }
  }
}
