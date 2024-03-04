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

  heatmap_ = std::vector<std::vector<float>>(
      width_, std::vector<float>(height_, lowest_depth_));

  insert_hotspots_();

  int smoothen_iteration_count = (rand() % 8) + 3;

  for (int k = 0; k < smoothen_iteration_count; k++) {
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
      } else if (heatmap_[i][j] >= 0.15) {
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

void HeatMap::insert_hotspots_() {
  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (rand() % 100 < hotspot_percentage_) {
        heatmap_[i][j] = highest_depth_;
      }
    }
  }
}

void HeatMap::smoothen_() {
  for (unsigned int i = 0; i < width_; i++) {
    for (unsigned int j = 0; j < height_; j++) {
      if (heatmap_[i][j] < highest_depth_) [[likely]] {
        float convolution_average = 0.0f;

        if (i == 0 && j == 0) {
          // Top left corner
          convolution_average = (heatmap_[i + 1][j] + heatmap_[i + 1][j + 1] +
                                 heatmap_[i][j + 1]) /
                                3.0f;
        } else if (i == width_ - 1 && j == 0) {
          // Top right corner
          convolution_average = (heatmap_[i][j + 1] + heatmap_[i - 1][j] +
                                 heatmap_[i - 1][j + 1]) /
                                3.0f;
        } else if (i == 0 && j == height_ - 1) {
          // Bottom left corner
          convolution_average = (heatmap_[i][j - 1] + heatmap_[i + 1][j] +
                                 heatmap_[i + 1][j - 1]) /
                                3.0f;
        } else if (i == width_ - 1 && j == height_ - 1) {
          // Bottom right corner
          convolution_average = (heatmap_[i][j - 1] + heatmap_[i - 1][j] +
                                 heatmap_[i - 1][j - 1]) /
                                3.0f;
        } else if (i == 0) {
          // Leftmost column
          convolution_average = (heatmap_[i][j + 1] + heatmap_[i + 1][j + 1] +
                                 heatmap_[i + 1][j] + heatmap_[i][j - 1] +
                                 heatmap_[i + 1][j - 1]) /
                                5.0f;
        } else if (i == width_ - 1) {
          // Rightmost column
          convolution_average = (heatmap_[i - 1][j + 1] + heatmap_[i][j + 1] +
                                 heatmap_[i - 1][j] + heatmap_[i - 1][j - 1] +
                                 heatmap_[i][j - 1]) /
                                5.0f;
        } else if (j == 0) {
          // Top row
          convolution_average = (heatmap_[i - 1][j] + heatmap_[i + 1][j] +
                                 heatmap_[i - 1][j + 1] + heatmap_[i][j + 1] +
                                 heatmap_[i + 1][j + 1]) /
                                5.0f;
        } else if (j == height_ - 1) {
          // Bottom row
          convolution_average = (heatmap_[i - 1][j - 1] + heatmap_[i][j - 1] +
                                 heatmap_[i + 1][j - 1] + heatmap_[i - 1][j] +
                                 heatmap_[i + 1][j]) /
                                5.0f;
        } else [[likely]] {
          // Normal grid point
          convolution_average = (heatmap_[i - 1][j + 1] + heatmap_[i][j + 1] +
                                 heatmap_[i + 1][j + 1] + heatmap_[i - 1][j] +
                                 heatmap_[i + 1][j] + heatmap_[i - 1][j - 1] +
                                 heatmap_[i][j - 1] + heatmap_[i + 1][j - 1]) /
                                8.0f;
        }

        float modifier_percentage = ((rand() % 100) + 1) / 100.0f;
        float increment = convolution_average * modifier_percentage;
        heatmap_[i][j] = std::min(heatmap_[i][j] + increment, highest_depth_);
      }
    }
  }
}
